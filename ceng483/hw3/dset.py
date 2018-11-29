import torch
import torchvision.transforms as transforms
import numpy as np
from torch.utils.data import Dataset, DataLoader
import utils

class ImageDataset(Dataset):
    def __init__(self, type="train" , transform=[] ):
        
        if(type=="train"):
            self.pictures = [x.strip("\n") for x in open("train.txt")]
        else:
            self.pictures = [x.strip("\n") for x in open("valid.txt")]
            
            
        
        self.transform = transform
        self.scaler = transforms.Resize((256, 256))
        self.to_tensor = transforms.ToTensor()
        self.normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                              std=[0.229, 0.224, 0.225])

        """
        L/100
        (A + 86.185)/184.439
        (B+107.863)/202.345
        """

    def __len__(self):
        return len(self.pictures)

    def __getitem__(self, idx):
        
        img_gray = utils.read_image("gray/"+self.pictures[idx])
        img_256 = utils.read_image("color_256/"+self.pictures[idx])
        
        #convert to L
        gray_L, _ = utils.cvt2Lab(img_gray)
        _, rgb_256_ab = utils.cvt2Lab(img_256)
        
        #normalize to [-1,1]
        gray_L = (gray_L-50)/50

        #normalize to [0,1]
        #gray_L, gray_ab[0], gray_ab[1]  = (gray_L)/100, (gray_ab[0]+86.185)/184.439 , (gray_ab[1]+107.863)/202.345
        #rgb_64_L, rgb_64_ab[0], rgb_64_ab[1] = (rgb_64_L)/100,  (rgb_64_ab[0]+86.185)/184.439 , (rgb_64_ab[1]+107.863)/202.345

        # HxWxC to CxHxW

        rgb_256_ab = np.transpose(rgb_256_ab , (2,0,1))
        
        #add 1 auxilary channel to L
        gray_L = np.expand_dims(gray_L,axis=0)
        
        rgb_256_ab = torch.from_numpy(rgb_256_ab)
        gray_L = torch.from_numpy(gray_L)

        
        
        
        """
        for trs in self.transform:
            img = trs(img)
        """
        
        #return gray_L, gray_ab, rgb_64_L, rgb_64_ab, rgb_256
        return gray_L, rgb_256_ab