import torch
import torchvision.transforms as transforms
import numpy as np
from torch.utils.data import Dataset, DataLoader
import glob
from PIL import Image


class AgeDataset(Dataset):
    def __init__(self, type="train" , transform=[] ):
        
        self.train_pictures = glob.glob("./train/*")
        self.val_pictures = glob.glob("./valid/*")
        if(type=="train"):
            self.pictures = self.train_pictures
            self.labels = np.load("./original/train_gt.npy")
        else:
            self.pictures = self.val_pictures
            self.labels = np.load("./original/valid_gt.npy")

        self.labels = torch.from_numpy(self.labels).view(-1,1).float()
            
        
        self.transform = transform
        self.scaler = transforms.Resize((224, 224))
        self.to_tensor = transforms.ToTensor()
        self.normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                              std=[0.229, 0.224, 0.225])

    def __len__(self):
        return len(self.pictures)

    def __getitem__(self, idx):
        
        img = Image.open(self.train_pictures[idx])
        img = img.resize((224, 224))
        img = self.scaler(img)

        for trs in self.transform:
            img = trs(img)

        img = self.to_tensor(img)
        if img.shape[0]==1:
            img = img.repeat(3,1,1)
        img = self.normalize(img)
        
        #if not (self.transform is None):
        #    sample = self.transform(sample)
        
        label = self.labels[idx]

        return img,label