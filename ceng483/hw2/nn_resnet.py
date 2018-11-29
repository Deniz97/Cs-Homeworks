import torch
import torchvision
import torchvision.transforms as transforms
import numpy as np
import matplotlib.pyplot as plt
from torch.utils.data import TensorDataset,Dataset, DataLoader
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.autograd import Variable
import random
import _pickle as pc


from dset import AgeDataset

SELECT_GPU = 3

torch.manual_seed(2)

#parameters
param = {}
param["l_rate"] = 0.001
param["epoch"] = 30
param["l2_rate"] = 0.0001
param["layers"] = [512,128,32]
param["drop"] = False
param["drop_p"] = 0.2
param["base_drop"] = False
param["base_drop_p"] = 0.1
param["batch_size"] = 64
param["batch_norm"] = False

#auxilary functions
def generate_random(a,b,percentage=0,default=-1,intmi=False):
    #returns default with a change of percentage
    if( np.random.ranf() > percentage ):
        retval= (b-a) * np.random.ranf() + a
    else:
        retval = default
    if(intmi==True):
        return int(retval)
    return retval

def get_random_architecture():
    length = random.choice([ 0,1,1, 2,2,3,3,3])
    retval = []
    old = 12
    for i in range(length):
        try:
            old = random.randint(1,old)
        except:
            return [500,200,50]
        retval.append(2**old)
    return retval

def random_params():
    global param
    param["l_rate"] = 10**(-generate_random(0,6,intmi=True))
    param["l2_rate"] = 10**(-generate_random(0,8,intmi=True))
    param["layers"] = get_random_architecture()
    
    ##init
    param["batch_norm"] = False
    param["drop"] = False
    param["drop_p"] = False
    ##
    param["batch_norm"] = random.choice([True, False])

    param["drop"] = random.choice([True, False])
    param["drop_p"] = generate_random(0,0.6)
    param["base_drop"] = random.choice([True, False])
    param["base_drop_p"] = generate_random(0,0.6)

    param["batch_size"] = random.choice([16,32,64,128,256,512,1024])
    
    param["epoch"] = 40 if sum(param["layers"]) < 2000 else 30

def mse_loss(a,b):
    a = a.data.numpy()
    b = b.numpy()
    return ((a - b)**2).mean(axis=None)

def calc_acc(pred,truth):
    pred =pred.data.view(-1).numpy()
    truth=truth.view(-1).numpy()
    assert pred.shape==truth.shape, "Shapes are not same"
    return (np.abs(pred-truth) < 10).sum() / pred.shape[0]

##

##NN models
class RS18(nn.Module):
    def __init__(self):

        super(RS18, self).__init__()
        self.resnet = torchvision.models.resnet18(pretrained=True)
        self.resnet = self.resnet.cuda(SELECT_GPU)
        self.resnet.eval()
        for param in self.resnet.parameters():
            param.requires_grad = False

        self.extraction_layer = self.resnet._modules.get('avgpool')

    def forward(self, x):
        
        my_embedding = torch.zeros(x.shape[0], 512, 1, 1).cuda(SELECT_GPU)

        def copy_data(m, i, o):
            #print("o shape: ",o.shape)
            #print("my embed shape: ",my_embedding.shape)
            my_embedding.copy_(o.data)

        h = self.extraction_layer.register_forward_hook(copy_data)
        h_x = self.resnet(x)
        h.remove()

        # feature pyramid network computations here

        return my_embedding.view(-1,512)


class Net(nn.Module):
    def __init__(self):
        super(Net,self).__init__()
        self.rs18 = RS18().cuda(SELECT_GPU)
        self.rs18 = self.rs18.cuda(SELECT_GPU)
        l = param["layers"]
        if(len(l)==0):
            self.fc1 = nn.Linear(512,1)
        elif(len(l)==1):
            self.fc1 = nn.Linear(512,l[0])
            self.fc2 = nn.Linear(l[0],1)
            if param["batch_norm"]==True:
                self.bn1 = nn.BatchNorm1d(l[0])
        elif(len(l)==2):
            self.fc1 = nn.Linear(512,l[0])
            self.fc2 = nn.Linear(l[0],l[1])
            self.fc3 = nn.Linear(l[1],1)
            if param["batch_norm"]==True:
                self.bn1 = nn.BatchNorm1d(l[0])
                self.bn2 = nn.BatchNorm1d(l[1])
        elif(len(l)==3):
            self.fc1 = nn.Linear(512,l[0])
            self.fc2 = nn.Linear(l[0],l[1])
            self.fc3 = nn.Linear(l[1],l[2])
            self.fc4 = nn.Linear(l[2],1)
            if param["batch_norm"]==True:
                self.bn1 = nn.BatchNorm1d(l[0])
                self.bn2 = nn.BatchNorm1d(l[1])
                self.bn3 = nn.BatchNorm1d(l[2])
        if param["drop"]==True :
            self.drop = nn.Dropout(p=param["drop_p"])
            
        if param["base_drop"]==True :
            self.base_drop = nn.Dropout(p=param["base_drop_p"])
        
    def forward(self,x):
        ##first extract feature
        
        x = self.rs18(x)
        x = x.view(-1,512)
        x = Variable(x).cuda(SELECT_GPU)
        
        l = param["layers"]
        if param["base_drop"]==True :
            x = self.base_drop(x)
        if(len(l)==0):
            x = self.fc1(x)
        elif(len(l)==1):
            x = self.fc1(x)
            if param["drop"]==True :
                x=self.drop(x)
            if param["batch_norm"]==True:
                x = self.bn1(x)
            x = F.relu(x)
            x = self.fc2(x)
        elif(len(l)==2):
            x = self.fc1(x)
            if param["drop"]==True :
                x=self.drop(x)
            if param["batch_norm"]==True:
                x = self.bn1(x)
            x = F.relu(x)
            x = self.fc2(x)
            if param["batch_norm"]==True:
                x = self.bn2(x)
            x = F.relu(x)
            x = self.fc3(x)
        elif(len(l)==3):
            x = self.fc1(x)
            if param["drop"]==True :
                x=self.drop(x)
            if param["batch_norm"]==True:
                x = self.bn1(x)
            x = F.relu(x)
            x = self.fc2(x)
            if param["batch_norm"]==True:
                x = self.bn2(x)
            x = F.relu(x)
            x = self.fc3(x)
            if param["batch_norm"]==True:
                x = self.bn3(x)
            x = F.relu(x)
            x = self.fc4(x)
        return x
##


def train(net):
    net = net.cuda(SELECT_GPU)
    net.train()
    optimizer = optim.RMSprop( filter(lambda p: p.requires_grad, net.parameters()) ,lr=param["l_rate"], weight_decay=param["l2_rate"])
    criterion = nn.MSELoss()
    log_interval = 5
    train_loss_list = []
    val_loss_list = []
    train_accuracy_list = []
    val_accuracy_list = []
    
    for epoch in range(param["epoch"]):
        
        net.train()
        for batch_idx, (data,target) in enumerate(dataloader):
            data,target = Variable(data),Variable(target)
            target = target.cuda(SELECT_GPU)
            #resize
            #data = data.view(-1,512)
            optimizer.zero_grad()
            data = data.cuda(SELECT_GPU)
            net_out = net(data)
            loss = criterion(net_out,target)
            
            loss.backward()
            optimizer.step()            
            if batch_idx % log_interval == 0:
                train_loss_list.append(int(loss[0]))
        
        
        if True:
            net.eval()
            #net = net.cpu()
            
            val_accuracy = 0
            val_loss = 0
            counter = 0
            for a,b in dataloader_val:
                a = Variable(a, requires_grad=False)
                a=a.cuda(SELECT_GPU)
                net_out_val = net(a)
                net_out_val = net_out_val.cpu()
                temp =calc_acc(net_out_val,b)
                val_accuracy += temp
                #print("val acc: ",temp)
                #print("b shape: ",b.shape)
                #print("a shape: ",a.shape)
                val_loss += int(mse_loss(net_out_val,b))
                counter += 1
            
            val_accuracy /= counter
            val_loss /= counter


            val_loss_list.append(val_loss)
            val_accuracy_list.append(val_accuracy)
        """
        net.eval()
        net_out_train = net(Variable(x_train))
        train_accuracy = calc_acc(net_out_train,y_train)
        train_loss = int(mse_loss(net_out_train,y_train))

        net_out_val = net(Variable(x_val))
        val_accuracy = calc_acc(net_out_val,y_val)
        val_loss = int(mse_loss(net_out_val,y_val))

        train_loss_list.append(train_loss)
        train_accuracy_list.append(train_accuracy)
        val_loss_list.append(val_loss)
        val_accuracy_list.append(val_accuracy)
        """
        
        print('Train Epoch: {}\tLoss: {:.4f}\tAcc: {:.4f}'.format(
                    epoch, loss.data[0],val_accuracy))

    return train_loss_list, val_loss_list,  train_accuracy_list, val_accuracy_list
                
        

if __name__ == '__main__':
        
    x_train = np.load("./original/train.npy")
    y_train = np.load("./original/train_gt.npy")
    x_val = np.load("./original/valid.npy")
    y_val = np.load("./original/valid_gt.npy")

    x_train = torch.from_numpy(x_train)
    y_train = torch.from_numpy(y_train).view(-1,1).float()
    x_val = torch.from_numpy(x_val)
    y_val = torch.from_numpy(y_val).view(-1,1).float()

    """
    age_dataset = TensorDataset(x_train,y_train)
    age_dataset_val = TensorDataset(x_val,y_val)
    dataloader = DataLoader(age_dataset, batch_size=param["batch_size"],
                            shuffle=True, num_workers=4)
    """

    transform_list = []
    transform_list.append(transforms.RandomVerticalFlip())
    transform_list.append(transforms.RandomResizedCrop(224))
    transform_list.append(transforms.RandomRotation(20))
    

    age_dataset = AgeDataset(transform=transform_list)
    dataloader = DataLoader(age_dataset, batch_size=param["batch_size"],
                            shuffle=True, num_workers=4)

    age_dataset_val = AgeDataset(type="val")
    dataloader_val = DataLoader(age_dataset_val, batch_size=250,
                            shuffle=True, num_workers=4)

    while True:
        
        print()
        print(param)
        print()
        net=Net()
        net = net.cuda(SELECT_GPU)
        train_loss_list, val_loss_list, train_accuracy_list, val_accuracy_list = train(net)

        param["max_val_acc"] = max(val_accuracy_list)
        param["min_val_loss"] = min(val_loss_list)
        param["max_train_acc"] = -1 #max(train_accuracy_list)
        param["min_train_loss"] = min(train_loss_list)
        
        print()
        print("Max acc: ",param["max_val_acc"])
        print("Min loss: ",param["min_val_loss"])
        print("Max acc (train): ",param["max_train_acc"])
        print("Min loss (train): ",param["min_train_loss"])
        print()
        print("---------")
        """
        plt.plot(train_loss_list, label="train loss")
        plt.plot(val_loss_list, label="val loss")
        plt.legend()
        plt.show()
        plt.plot(train_accuracy_list,label="train acc")
        plt.plot(val_accuracy_list,label="val acc")
        plt.ylim((0.4,0.7))
        plt.legend()
        plt.show()
        """

        with open("logs_resnet.p","ab") as filem:
            pc.dump(param,filem)
        


