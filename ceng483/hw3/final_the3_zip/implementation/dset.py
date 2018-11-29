import torch
import torchvision.transforms as transforms
import numpy as np
from torch.utils.data import Dataset, DataLoader
import utils

class ImageDataset(Dataset):
    def __init__(self, d_type="train" , transform=[] ):
        
        self.d_type = d_type

        if d_type=="train":
            self.pictures = [x.strip("\n") for x in open("train.txt")]
        elif d_type=="valid":
            self.pictures = [x.strip("\n") for x in open("valid.txt")]
        elif d_type=="train-valid":
            self.pictures = [x.strip("\n") for x in open("train.txt")] + [x.strip("\n") for x in open("valid.txt")]
        elif d_type=="test":
            self.pictures = [x.strip("\n") for x in open("test.txt")]
        else:
            assert False, "Not known data type"

        """
        L/100
        (A + 86.185)/184.439
        (B+107.863)/202.345
        """

    def __len__(self):
        return len(self.pictures)

    def __getitem__(self, idx):
        
        ### TEST DATASET
        if self.d_type=="test":
            img_gray = utils.read_image("test_gray/"+self.pictures[idx])
            
            #convert to Lab
            gray_L, gray_ab = utils.cvt2Lab(img_gray)

            #normalize to [-1,1]
            #gray_L, gray_ab = (gray_L-50)/50, gray_ab/128
            gray_L = (gray_L-50)/50
            
            #normalize to [0,1]
            #gray_L, gray_ab[0], gray_ab[1]  = (gray_L)/100, (gray_ab[0]+86.185)/184.439 , (gray_ab[1]+107.863)/202.345
            
            #add 1 auxilary channel to L
            gray_L = np.expand_dims(gray_L,axis=0)
            
            
            #rgb_256 = torch.from_numpy(rgb_256)
            gray_L = torch.from_numpy(gray_L)
            #gray_ab = torch.from_numpy(gray_ab)
            
            return gray_L


        ### TEST DATASET END 
        

        img_gray = utils.read_image("gray/"+self.pictures[idx])
        img_64 = utils.read_image("color_64/"+self.pictures[idx])
        
        #convert to Lab
        gray_L, gray_ab = utils.cvt2Lab(img_gray)
        rgb_64_L, rgb_64_ab = utils.cvt2Lab(img_64)
        
        #normalize to [-1,1]
        gray_L, gray_ab = (gray_L-50)/50, gray_ab/128
        rgb_64_L, rgb_64_ab = (rgb_64_L-50)/50 , rgb_64_ab/128

        #normalize to [0,1]
        #gray_L, gray_ab[0], gray_ab[1]  = (gray_L)/100, (gray_ab[0]+86.185)/184.439 , (gray_ab[1]+107.863)/202.345
        #rgb_64_L, rgb_64_ab[0], rgb_64_ab[1] = (rgb_64_L)/100,  (rgb_64_ab[0]+86.185)/184.439 , (rgb_64_ab[1]+107.863)/202.345

        # HxWxC to CxHxW
        rgb_64_ab = np.transpose(rgb_64_ab , (2,0,1))
        gray_ab = np.transpose(gray_ab , (2,0,1))
        
        #add 1 auxilary channel to L
        gray_L = np.expand_dims(gray_L,axis=0)
        rgb_64_L = np.expand_dims(rgb_64_L,axis=0)
        
        #to torch tensor
        gray_L = torch.from_numpy(gray_L)
        gray_ab = torch.from_numpy(gray_ab)
        rgb_64_L = torch.from_numpy(rgb_64_L)
        rgb_64_ab = torch.from_numpy(rgb_64_ab)
        
        
        """
        for trs in self.transform:
            img = trs(img)
        """
        
        return gray_L, gray_ab, rgb_64_L, rgb_64_ab