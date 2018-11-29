import torch
import torchvision
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from torch.utils.data import TensorDataset,Dataset, DataLoader
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.autograd import Variable
import random
import _pickle as pc
import warnings
from PIL import Image

import utils
from dset import ImageDataset

torch.manual_seed(17)

SELECT_GPU = 0
go_cuda = False

#parameters
param = {}
param["l_rate"] = 0.1
param["epoch"] = 50
param["l2_rate"] = 0.0001
param["batch_size"] = 128

param["kernel1"] = 16
param["kernel2"] = 24

param["normalization"] = "-1,1" #0,1, -1,1
param["init"] = "default" #"he-normal"
param["decay_param"] = "val-loss"
#####auxilary functions

def default_param():
    global param
    param["epoch"] = 31
    param["l2_rate"] = 0.00001
    param["batch_size"] = 16
    param["l_rate"] = 0.001

    param["decay"] = 0.2
    param["kernel1"] = 48
    param["kernel2"] = 16
  

def generate_random(a,b,percentage=0,default=-1,intmi=False):
    #returns default with a change of percentage
    if( np.random.ranf() > percentage ):
        retval= (b-a) * np.random.ranf() + a
    else:
        retval = default
    if(intmi==True):
        return int(retval)
    return retval


def random_param():
    global param
    param["l_rate"] = 10**(-generate_random(0,3,intmi=True))
    param["l2_rate"] = 10**(-generate_random(1,6,intmi=True))
    #param["decay_step_size"] = random.choice([4,8,16])
    param["decay"] = random.choice([0.1,0.2,0.4])
    param["kernel1"] = random.choice([16,24,32,40,48])
    param["kernel2"] = random.choice([16,24,32,40,48])
    param["batch_size"] = random.choice([16,32,64,128,256])
    
    param["epoch"] = 30

def mse_loss(a,b):
    a = a.data.numpy()
    b = b.data.numpy()
    return ((a - b)**2).mean(axis=None)



def calc_acc(estimations,names_file):
    with open(names_file, "r") as f:
        files = f.readlines()
    acc = 0
    for i, filem in enumerate(files):
        cur = utils.read_image("color_256/" + filem.rstrip()).reshape(-1).astype(np.int64)
        est = estimations[i].reshape(-1).astype(np.int64)
    
        cur_acc = (np.abs(cur - est) < 12).sum() / cur.shape[0]
        acc += cur_acc
    acc /= len(files)
    
    return acc
#####auxilary functions END

class Net(nn.Module):
    def __init__(self):
        super(Net,self).__init__()

        self.conv1 = nn.Conv2d(1,param["kernel1"],(5,5),padding=2)
        self.maxpool1 = nn.MaxPool2d(2,2)
        self.bn1 = nn.BatchNorm2d(param["kernel1"])

        self.conv2 = nn.Conv2d(param["kernel1"],param["kernel2"],(3,3),padding=1)
        self.maxpool2 = nn.MaxPool2d(2,2)
        self.bn2 = nn.BatchNorm2d(param["kernel2"])

        self.conv3 = nn.Conv2d(param["kernel2"],2,(3,3),padding=1)
               
    def forward(self,x):    
        x = self.conv1(x)
        x = self.maxpool1(x)
        x = self.bn1(x)
        x = F.relu(x)

        x = self.conv2(x)
        x = self.maxpool2(x)
        x = self.bn2(x)
        x = F.relu(x)

        x = self.conv3(x)
        return x


train_dset = ImageDataset(d_type="train")
val_dset = ImageDataset(d_type="valid")
test_dset = ImageDataset(d_type="test")
train_loader = DataLoader(train_dset, batch_size=param["batch_size"],
                        shuffle=True, num_workers=4)
acc_train_loader = DataLoader(train_dset, batch_size=len(train_dset),
                        shuffle=False, num_workers=4)
acc_val_loader = DataLoader(val_dset, batch_size=len(val_dset),
                        shuffle=False, num_workers=4)
acc_test_loader = DataLoader(test_dset, batch_size=len(test_dset),
                        shuffle=False, num_workers=4)


def toRgb256(L,ab):
    L = L.data.numpy()
    ab = ab.data.numpy()
    
    assert L.shape[0]==ab.shape[0],"Unmatching batch sizes"
    
    ab = np.transpose(ab,(0,2,3,1))
    L = np.transpose(L,(0,2,3,1))

    ab[ab>1] = 1
    ab[ab<-1] = -1
    #upsample form 64 to 256
    upsampled_ab = np.zeros((ab.shape[0],256,256,2)).astype(np.float64)
    for i in range(ab.shape[0]):
        upsampled_ab[i] = utils.upsample(ab[i]) 
    ab = upsampled_ab


    #denormalize from [-1,1] to [-128,127]
    ab = ab*128
    ab[ab>127] = 127
    ab[ab<-128] = -128
    #denormalize from [-1,1] to [0,100]
    L = L*50+50
    L[L>100] = 100
    L[L<0] = 0
    """
    #denormalize from [0,1] to [-128,127]
    ab[0] = ab[0]*184.439-86.185
    ab[1] = ab[1]*202.345-107.863
    ab[ab>127] = 127
    ab[ab<-128] = -128
    #denormalize from [0,1] to [0,100]
    L = L*100
    L[L>100] = 100
    L[L<0] = 0
    """
    assert L.shape[0]==ab.shape[0] and L.shape[1:3] == ab.shape[1:3],"Unmatching shapes sizes"

    lab_img = np.stack((L[:,:,:,0],ab[:,:,:,0],ab[:,:,:,1]),axis=3)
    
    for i in range(lab_img.shape[0]):
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            lab_img[i] = utils.cvt2rgb(lab_img[i])*255

    return lab_img.astype(np.uint8)




def train(net):
    net.train()
    optimizer = optim.RMSprop(net.parameters(),lr=param["l_rate"], weight_decay=param["l2_rate"])
    #scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=param["decay_step_size"], gamma=param["decay"])
    scheduler = optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode="min", factor=param["decay"],patience=5)
    criterion = nn.MSELoss()
    log_interval = 1
    train_loss_list = []
    val_loss_list = []
    train_accuracy_list = []
    val_accuracy_list = []
    #try-catch block, to be able to cut current experiment early if accuracies does not look promising

    for epoch in range(param["epoch"]):
        net.train()
        train_loss = 0
        train_accuracy = 0 #not used right now
        if go_cuda:
            net = net.cuda(SELECT_GPU)
        
        for batch_idx, (gray_L, gray_ab, rgb_64_L, rgb_64_ab) in enumerate(train_loader):
            
            gray_L,rgb_64_ab = Variable(gray_L).float() ,Variable(rgb_64_ab).float()
            
            if go_cuda:
                gray_L = gray_L.cuda(SELECT_GPU)
                rgb_64_ab = rgb_64_ab.cuda(SELECT_GPU)
                
            #resize
            optimizer.zero_grad()
            pred_rgb_64_ab = net(gray_L)
            
            loss = criterion(pred_rgb_64_ab,rgb_64_ab)
            train_loss += float(loss)/gray_L.shape[0]    
            loss.backward()
            optimizer.step()

        net.eval()
        
        #training loss and accuracy
        
        """
        print("training eval")
        for index, (gray_L, gray_ab, rgb_64_L, rgb_64_ab) in enumerate(acc_train_loader):
            gray_L,rgb_64_ab = Variable(gray_L),Variable(rgb_64_ab)
            pred_rgb_64_ab = net(gray_L)
            assert index<1, "This loop should not run more than once"
        train_loss = int(mse_loss(pred_rgb_64_ab,rgb_64_ab))
        pred_rgb_256 = toRgb256(gray_L,pred_rgb_64_ab)
        train_accuracy = calc_acc(pred_rgb_256,"train.txt")
        """
        if go_cuda:
            net = net.cpu()
        for index, (gray_L, gray_ab, rgb_64_L, rgb_64_ab) in enumerate(acc_val_loader):
            gray_L,rgb_64_ab = Variable(gray_L).float(),Variable(rgb_64_ab).float()
            pred_rgb_64_ab = net(gray_L)
            assert index<1, "This loop should not run more than once"
        val_loss = float(mse_loss(pred_rgb_64_ab,rgb_64_ab))
        pred_rgb_256 = toRgb256(gray_L,pred_rgb_64_ab)
        val_accuracy = calc_acc(pred_rgb_256,"valid.txt")

        img = Image.fromarray(pred_rgb_256[-1], 'RGB')
        img.save('my.png')
        
        img = Image.fromarray(pred_rgb_256[1], 'RGB')
        img.save('my2.png')
        
        img = Image.fromarray(pred_rgb_256[2], 'RGB')
        img.save('my3.png')

        train_loss_list.append(train_loss)
        train_accuracy_list.append(train_accuracy)
        val_loss_list.append(val_loss)
        val_accuracy_list.append(val_accuracy)

        scheduler.step(val_loss)
        if((epoch+1)%log_interval==0 or epoch==0):
            print('Train Epoch: {}\tTrain Loss: {:.6f}\tVal Loss: {:.6f}\tVal Acc: {:.4f}'.format(
                    epoch, train_loss, val_loss, val_accuracy))
        

            
    
    return train_loss_list, val_loss_list,  train_accuracy_list, val_accuracy_list
                
        

def run_test(net):
    print("starting test run")
    
    net.eval()
    #make inferences on test_loader
    for index, gray_L in enumerate(acc_test_loader):
            gray_L = Variable(gray_L).float()
            pred_rgb_64_ab = net(gray_L)
            assert index<1, "This loop should not run more than once"
    #transform to rgb_256
    pred_rgb_256 = toRgb256(gray_L,pred_rgb_64_ab)
    
    print()
    with open("estimations_test.npy","wb") as filem:
        np.save(filem,pred_rgb_256)
    print(pred_rgb_256.shape)
    print()
    print(pred_rgb_256)
    print("done testing")



if __name__ == '__main__':
    for i in range(1):
        default_param()
        #random_param()
            
        print()
        print(param)
        print()
        torch.manual_seed(17)
        net=Net()
        
        def weights_init(m):
            if isinstance(m, nn.Conv2d):
                nn.init.kaiming_normal_(m.weight.data, mode='fan_out', nonlinearity='relu')
        if param["init"]=="he-normal":
            net.apply(weights_init)


        train_loss_list, val_loss_list, train_accuracy_list, val_accuracy_list = train(net)



        print()
        print("train loss list: ",train_loss_list)
        print("val loss list: ",val_loss_list)
        print("train acc list: ",train_accuracy_list)
        print("val acc list: ",val_accuracy_list)
        print()
        param["max_val_acc"] = max(val_accuracy_list)
        param["min_val_loss"] = min(val_loss_list)
        param["max_train_acc"] = max(train_accuracy_list) if len(train_accuracy_list) > 0 else -1
        param["min_train_loss"] = min(train_loss_list)
        param["last_ten_val_acc"] = sum( val_accuracy_list[-10:]  )/10
        param["last_five_val_acc"] = sum( val_accuracy_list[-5:]  )/5
        net.eval()
        
        print()
        print("Avg acc ten: ",param["last_ten_val_acc"])
        print("Avg acc five: ",param["last_five_val_acc"] )
        print("Max acc: ",param["max_val_acc"])
        print("Min loss: ",param["min_val_loss"])
        print("Max acc (train): ",param["max_train_acc"])
        print("Min loss (train): ",param["min_train_loss"])
        print()
        print("---------")
        
        
        plt.plot(train_loss_list, label="Train. Loss")
        plt.plot(val_loss_list, label="Val. Loss")
        plt.legend()
        plt.savefig('lossplot.png')
        #plt.show()
        plt.plot(train_accuracy_list,label="Train Acc.")
        plt.plot(val_accuracy_list,label="Val. Acc.")
        plt.ylim((0.2,0.8))
        plt.legend()
        plt.savefig('accplot.png')
        #plt.show()
        

        with open("logs.p","ab") as filem:
            pc.dump(param,filem)
        with open("logs.txt","a") as filem:
            filem.write(str(param)+"\n\n" )
            filem.write(str(train_loss_list)+"\n\n" )
            filem.write(str(val_loss_list)+"\n\n" )
            filem.write(str(train_accuracy_list)+"\n\n" )
            filem.write(str(val_accuracy_list)+"\n\n" )
            filem.write("--------------------------"+"\n\n\n" )
            print("Saved logs to file.")

        run_test(net)




