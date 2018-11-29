import torch
import torchvision
import numpy as np
import matplotlib.pyplot as plt
from torch.utils.data import TensorDataset,Dataset, DataLoader
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.autograd import Variable
import random
import _pickle as pc
import glob

from PIL import Image

from img_to_vec import Img2Vec
from dset import AgeDataset

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
param["batch_size"] = 8
param["batch_norm"] = False

def default_param(number_of_layers):
    global param
    param["epoch"] = 50
    param["l2_rate"] = 0
    param["drop"] = True
    param["base_drop"] = True
    param["base_drop_p"] = 0.2
    param["drop_p"] = 0.2
    param["batch_size"] = 8
    param["batch_norm"] = True
    if number_of_layers==3:
        param["drop"] = True
        param["base_drop"] = True
        param["l_rate"] = 0.0001
        param["layers"] = [512,128,32]
    elif number_of_layers==2:
        param["l_rate"] = 0.0001
        param["layers"] = [256,64]
        param["drop"] = True
        param["base_drop"] = True
    elif number_of_layers==1:
        param["l_rate"] = 0.001
        param["layers"] = [128]
        param["drop"] = True
        param["base_drop"] = True
    elif number_of_layers==0:
        param["drop"] = False
        param["base_drop"] = False
        param["base_drop_p"] = 0
        param["drop_p"] = 0
        param["l_rate"] = 0.001
        param["layers"] = []
    else:
        assert False, "Unknown number of layers"

    

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
    length = random.choice([0, 1,1, 2,2,3,3,3])
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
    
    param["epoch"] = 50 if sum(param["layers"]) < 2000 else 30

def mse_loss(a,b):
    a = a.data.numpy()
    b = b.numpy()
    return ((a - b)**2).mean(axis=None)


#auxilary functions
def calc_acc(pred,truth):
    pred =pred.data.view(-1).numpy()
    truth=truth.view(-1).numpy()
    assert pred.shape==truth.shape, "Shapes are not same"
    return (np.abs(pred-truth) < 10).sum() / pred.shape[0]


class Net(nn.Module):
    def __init__(self):
        super(Net,self).__init__()
        
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



def train(net):
    net.train()
    optimizer = optim.RMSprop(net.parameters(),lr=param["l_rate"], weight_decay=param["l2_rate"])
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
            #resize
            data = data.view(-1,512)
            optimizer.zero_grad()
            net_out = net(data)
            loss = criterion(net_out,target)
            
            loss.backward()
            optimizer.step()            
            if batch_idx % log_interval == 0:
                pass
                #train_loss_list.append(int(loss[0]))
        
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

        if((epoch+1)%1==0 or epoch==0):
            print('Train Epoch: {}\tLoss: {:.4f}\tAcc: {:.4f}'.format(
                    epoch, loss.data[0],val_accuracy))
        if val_accuracy > 0.62:
            break
    return train_loss_list, val_loss_list,  train_accuracy_list, val_accuracy_list
                
        

x_train = np.load("./original/train.npy")
y_train = np.load("./original/train_gt.npy")
x_val = np.load("./original/valid.npy")
y_val = np.load("./original/valid_gt.npy")
x_test = np.load("./original/test.npy")


x_test = torch.from_numpy(x_test)
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

age_dataset = TensorDataset(x_train,y_train)
dataloader = DataLoader(age_dataset, batch_size=param["batch_size"],
                        shuffle=True, num_workers=4)


def run_test():
    #SET PARAMETERS
    default_param(3)
    #
    net=Net()
    train(net)
    net.eval()
    net_out_test = net(Variable(x_test))
    net_out_test=net_out_test.data.view(-1).numpy()
    print()
    with open("estimations_test.npy","wb") as filem:
        np.save(filem,net_out_test)
    print(net_out_test.shape)
    print()
    print(net_out_test)

def run_pictures():
    #SET PARAMETERS
    default_param(3)
    #
    net=Net()
    train(net)
    net.eval()
    
    pics = glob.glob("./pictures/*")
    for pic in pics:
        fe = Img2Vec(cuda=False) # change this if you use Cuda version of the PyTorch.
        img = Image.open(pic)
        img = img.resize((224, 224))
        feats = fe.get_vec(img).reshape(1, -1)
        feats = torch.from_numpy(feats)
        print(pic)
        net_out = net(Variable(feats))
        print(net_out)

run_pictures()
exit()



counter = 3
while True:
    default_param(counter)
    for i in [0]:
        

        param["epoch"] = 100
        print()
        print(param)
        print()
        torch.manual_seed(2)
        net=Net()
        train_loss_list, val_loss_list, train_accuracy_list, val_accuracy_list = train(net)

        param["max_val_acc"] = max(val_accuracy_list)
        param["min_val_loss"] = min(val_loss_list)
        param["max_train_acc"] = max(train_accuracy_list)
        param["min_train_loss"] = min(train_loss_list)
        param["last_ten_val_acc"] = sum( val_accuracy_list[-10:]  )/10
        param["last_five_val_acc"] = sum( val_accuracy_list[-5:]  )/5
        net.eval()

        net_out_val = net(Variable(x_val))
        
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
        plt.show()
        plt.plot(train_accuracy_list,label="Train Acc.")
        plt.plot(val_accuracy_list,label="Val. Acc.")
        plt.ylim((0.2,0.8))
        plt.legend()
        plt.show()
        

        with open("logs.p","ab") as filem:
            pc.dump(param,filem)
        with open("logs.txt","a") as filem:
            filem.write(str(param)+"\n\n" )
        with open("logs.txt","a") as filem:
            filem.write(str(train_loss_list)+"\n\n" )
            filem.write(str(val_loss_list)+"\n\n" )
            filem.write(str(train_accuracy_list)+"\n\n" )
            filem.write(str(val_accuracy_list)+"\n\n" )
    with open("logs.txt","a") as filem:
                filem.write("--------------------------"+"\n\n\n" )
    counter += 1


"""
{'l_rate': 0.001, 'epoch': 100, 'l2_rate': 1e-05, 'layers': [1008], 'drop': False, 'drop_p': 0.7110156773892836, 'base_drop': False, 'base_drop_p': 0.6544765857182548, 'batch_size': 256, 'max_val_acc': 0.6335, 'min_val_loss': 158, 'max_train_acc': 0.8918, 'min_train_loss': 40}

"""




