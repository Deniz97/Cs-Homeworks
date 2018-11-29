/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)<(b))?(b):(a))

/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2172088",              /* Student ID */

    "Deniz Rasim Ulug",     /* full name */
    "deniz.ulug@metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * CONVOLUTION KERNEL
 ***************/

/******************************************************
 * Your different versions of the convolution functions  go here
 ******************************************************/

/* 
 * naive_conv - The naive baseline version of convolution 
 */

char naive_convbase_descr[] = "naive_conv: Naive baseline implementation base";
void naive_convbase(int dim,int *src, int *ker,int *dest) {
    int i,j,k,l;
    int sum;
    

    for(j = 0; j < dim-8+1; j++){

        for(l = 0; l < 8; l++){
            
            for(i = 0; i < dim-8+1; i++){
                
                for(k = 0; k < 8; k++){
                    dest[j*dim+i] += src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
                
            }
            
        }
    }         
        
}

char naive_convbasesondeneme_descr[] = "conv jilk son deneme";
void naive_convbasesondeneme(int dim,int *src, int *ker,int *dest) {
    int i,j,k,l;
    int sum;
    int jdim, idim, ldim, kdim;
    int *destin, *srcin, *kerin;
    

    for(j = 0; j < dim-7; j++){
        jdim=j*dim;
        destin = dest +jdim;
        for(i = 0; i < dim-7; i++){
            
            *destin=0;
            kerin = ker;
            srcin = src + jdim + i;
            
            //unrolling 64 starts

            for(l = 0; l < 8; l++){
                
                    (*(destin)) += (*(srcin)) * (*(kerin));
                    (*(destin)) += (*(srcin+1)) * (*(kerin+1));
                    (*(destin)) += (*(srcin+2)) * (*(kerin+2));
                    (*(destin)) += (*(srcin+3)) * (*(kerin+3));
                    (*(destin)) += (*(srcin+4)) * (*(kerin+4));
                    (*(destin)) += (*(srcin+5)) * (*(kerin+5));
                    (*(destin)) += (*(srcin+6)) * (*(kerin+6));
                    (*(destin)) += (*(srcin+7)) * (*(kerin+7));
                    
                    

            kerin += dim ;    
            srcin += dim ;
            }

            //unrolling 64 ends

        destin+=1;    
        }
    }         
        
}


char naive_convijlk_descr[] = "naive_conv: Naive baseline implementation ijlk";
void naive_convijlk(int dim,int *src, int *ker,int *dest) {
    int i,j,l;
    int sum;
    int *destin,*srcin,*kerin;
    
    srcin = src;
    destin = dest;
    for(j = 0; j < dim-7; j++){
        kerin = ker;
        //8l start
        //l=0
        for(i = 0; i < dim-11; i+=4){            
                sum=0;
                sum += (*(srcin)) * (*(kerin));
                sum += (*(srcin+1)) * (*(kerin+1));
                sum += (*(srcin+2)) * (*(kerin+2));
                sum += (*(srcin+3)) * (*(kerin+3));
                sum += (*(srcin+4)) * (*(kerin+4));
                sum += (*(srcin+5)) * (*(kerin+5));
                sum += (*(srcin+6)) * (*(kerin+6));
                sum += (*(srcin+7)) * (*(kerin+7));
                (*(destin)) = sum;    
                sum=0;
                sum += (*(srcin+1)) * (*(kerin));
                sum += (*(srcin+2)) * (*(kerin+1));
                sum += (*(srcin+3)) * (*(kerin+2));
                sum += (*(srcin+4)) * (*(kerin+3));
                sum += (*(srcin+5)) * (*(kerin+4));
                sum += (*(srcin+6)) * (*(kerin+5));
                sum += (*(srcin+7)) * (*(kerin+6));
                sum += (*(srcin+8)) * (*(kerin+7));
                (*(destin+1)) = sum;   
                sum=0;
                sum += (*(srcin+2)) * (*(kerin));
                sum += (*(srcin+3)) * (*(kerin+1));
                sum += (*(srcin+4)) * (*(kerin+2));
                sum += (*(srcin+5)) * (*(kerin+3));
                sum += (*(srcin+6)) * (*(kerin+4));
                sum += (*(srcin+7)) * (*(kerin+5));
                sum += (*(srcin+8)) * (*(kerin+6));
                sum += (*(srcin+9)) * (*(kerin+7));
                (*(destin+2)) = sum;
                sum=0;
                sum += (*(srcin+3)) * (*(kerin));
                sum += (*(srcin+4)) * (*(kerin+1));
                sum += (*(srcin+5)) * (*(kerin+2));
                sum += (*(srcin+6)) * (*(kerin+3));
                sum += (*(srcin+7)) * (*(kerin+4));
                sum += (*(srcin+8)) * (*(kerin+5));
                sum += (*(srcin+9)) * (*(kerin+6));
                sum += (*(srcin+10)) * (*(kerin+7));
                (*(destin+3)) = sum;
                destin+=4;
                srcin+=4;
            }
            sum=0;
            sum += (*(srcin)) * (*(kerin));
            sum += (*(srcin+1)) * (*(kerin+1));
            sum += (*(srcin+2)) * (*(kerin+2));
            sum += (*(srcin+3)) * (*(kerin+3));
            sum += (*(srcin+4)) * (*(kerin+4));
            sum += (*(srcin+5)) * (*(kerin+5));
            sum += (*(srcin+6)) * (*(kerin+6));
            sum += (*(srcin+7)) * (*(kerin+7));
            (*(destin)) = sum;
            srcin += 8;
            destin -= (dim - 8) ;
            kerin += dim;

        //l rest
        for(l=1;l<8;l++){
            for(i = 0; i < dim-11; i+=4){  
                sum=0;
                sum += (*(srcin)) * (*(kerin));
                sum += (*(srcin+1)) * (*(kerin+1));
                sum += (*(srcin+2)) * (*(kerin+2));
                sum += (*(srcin+3)) * (*(kerin+3));
                sum += (*(srcin+4)) * (*(kerin+4));
                sum += (*(srcin+5)) * (*(kerin+5));
                sum += (*(srcin+6)) * (*(kerin+6));
                sum += (*(srcin+7)) * (*(kerin+7));
                (*(destin)) += sum;   
                sum=0;
                sum += (*(srcin+1)) * (*(kerin));
                sum += (*(srcin+2)) * (*(kerin+1));
                sum += (*(srcin+3)) * (*(kerin+2));
                sum += (*(srcin+4)) * (*(kerin+3));
                sum += (*(srcin+5)) * (*(kerin+4));
                sum += (*(srcin+6)) * (*(kerin+5));
                sum += (*(srcin+7)) * (*(kerin+6));
                sum += (*(srcin+8)) * (*(kerin+7));
                (*(destin+1)) += sum;
                sum=0;
                sum += (*(srcin+2)) * (*(kerin));
                sum += (*(srcin+3)) * (*(kerin+1));
                sum += (*(srcin+4)) * (*(kerin+2));
                sum += (*(srcin+5)) * (*(kerin+3));
                sum += (*(srcin+6)) * (*(kerin+4));
                sum += (*(srcin+7)) * (*(kerin+5));
                sum += (*(srcin+8)) * (*(kerin+6));
                sum += (*(srcin+9)) * (*(kerin+7));
                (*(destin+2)) += sum;    
                sum=0;
                sum += (*(srcin+3)) * (*(kerin));
                sum += (*(srcin+4)) * (*(kerin+1));
                sum += (*(srcin+5)) * (*(kerin+2));
                sum += (*(srcin+6)) * (*(kerin+3));
                sum += (*(srcin+7)) * (*(kerin+4));
                sum += (*(srcin+8)) * (*(kerin+5));
                sum += (*(srcin+9)) * (*(kerin+6));
                sum += (*(srcin+10)) * (*(kerin+7));
                (*(destin+3)) += sum;
                destin+=4;
                srcin+=4;
            }
            sum=0;
            sum += (*(srcin)) * (*(kerin));
            sum += (*(srcin+1)) * (*(kerin+1));
            sum += (*(srcin+2)) * (*(kerin+2));
            sum += (*(srcin+3)) * (*(kerin+3));
            sum += (*(srcin+4)) * (*(kerin+4));
            sum += (*(srcin+5)) * (*(kerin+5));
            sum += (*(srcin+6)) * (*(kerin+6));
            sum += (*(srcin+7)) * (*(kerin+7));
            (*(destin)) += sum;
            srcin += 8;
            destin -= (dim - 8) ;
            kerin += dim;
        }
        //8l end
    srcin -= (7*(dim)); 
    destin +=  dim;
    }         
        
}



char naive_convijlkcrazyunroll_descr[] = "naive_conv: Naive baseline implementation ijlk crazy unroll";
void naive_convijlkcrazyunroll(int dim,int *src, int *ker,int *dest) {
    int i,j;
    int sum;
    int *kerin;
    int dm15 = dim-15;


    for(j = 0; j < dim-7; j++){
        kerin = ker;
        //8l start
        //l=0
            for(i = 0; i < dm15; i+=8){
                sum=0;
                sum += (*(src)) * (*(kerin));
                sum += (*(src+1)) * (*(kerin+1));
                sum += (*(src+2)) * (*(kerin+2));
                sum += (*(src+3)) * (*(kerin+3));
                sum += (*(src+4)) * (*(kerin+4));
                sum += (*(src+5)) * (*(kerin+5));
                sum += (*(src+6)) * (*(kerin+6));
                sum += (*(src+7)) * (*(kerin+7));
                (*(dest)) = sum;
                sum=0;
                sum += (*(src+1)) * (*(kerin));
                sum += (*(src+2)) * (*(kerin+1));
                sum += (*(src+3)) * (*(kerin+2));
                sum += (*(src+4)) * (*(kerin+3));
                sum += (*(src+5)) * (*(kerin+4));
                sum += (*(src+6)) * (*(kerin+5));
                sum += (*(src+7)) * (*(kerin+6));
                sum += (*(src+8)) * (*(kerin+7));
                (*(dest+1)) = sum;
                sum=0;
                sum += (*(src+2)) * (*(kerin));
                sum += (*(src+3)) * (*(kerin+1));
                sum += (*(src+4)) * (*(kerin+2));
                sum += (*(src+5)) * (*(kerin+3));
                sum += (*(src+6)) * (*(kerin+4));
                sum += (*(src+7)) * (*(kerin+5));
                sum += (*(src+8)) * (*(kerin+6));
                sum += (*(src+9)) * (*(kerin+7));
                (*(dest+2)) = sum;
                sum=0;
                sum += (*(src+3)) * (*(kerin));
                sum += (*(src+4)) * (*(kerin+1));
                sum += (*(src+5)) * (*(kerin+2));
                sum += (*(src+6)) * (*(kerin+3));
                sum += (*(src+7)) * (*(kerin+4));
                sum += (*(src+8)) * (*(kerin+5));
                sum += (*(src+9)) * (*(kerin+6));
                sum += (*(src+10)) * (*(kerin+7));
                (*(dest+3)) = sum;

              
                sum=0;
                sum += (*(src+4)) * (*(kerin));
                sum += (*(src+5)) * (*(kerin+1));
                sum += (*(src+6)) * (*(kerin+2));
                sum += (*(src+7)) * (*(kerin+3));
                sum += (*(src+8)) * (*(kerin+4));
                sum += (*(src+9)) * (*(kerin+5));
                sum += (*(src+10)) * (*(kerin+6));
                sum += (*(src+11)) * (*(kerin+7));
                (*(dest+4)) = sum;
                
            
                sum=0;
                sum += (*(src+5)) * (*(kerin));
                sum += (*(src+6)) * (*(kerin+1));
                sum += (*(src+7)) * (*(kerin+2));
                sum += (*(src+8)) * (*(kerin+3));
                sum += (*(src+9)) * (*(kerin+4));
                sum += (*(src+10)) * (*(kerin+5));
                sum += (*(src+11)) * (*(kerin+6));
                sum += (*(src+12)) * (*(kerin+7));
                (*(dest+5)) = sum;
                
            
                sum=0;
                sum += (*(src+6)) * (*(kerin));
                sum += (*(src+7)) * (*(kerin+1));
                sum += (*(src+8)) * (*(kerin+2));
                sum += (*(src+9)) * (*(kerin+3));
                sum += (*(src+10)) * (*(kerin+4));
                sum += (*(src+11)) * (*(kerin+5));
                sum += (*(src+12)) * (*(kerin+6));
                sum += (*(src+13)) * (*(kerin+7));
                (*(dest+6)) = sum;
                
             
                sum=0;
                sum += (*(src+7)) * (*(kerin));
                sum += (*(src+8)) * (*(kerin+1));
                sum += (*(src+9)) * (*(kerin+2));
                sum += (*(src+10)) * (*(kerin+3));
                sum += (*(src+11)) * (*(kerin+4));
                sum += (*(src+12)) * (*(kerin+5));
                sum += (*(src+13)) * (*(kerin+6));
                sum += (*(src+14)) * (*(kerin+7));
                (*(dest+7)) = sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src)) * (*(kerin));
            sum += (*(src+1)) * (*(kerin+1));
            sum += (*(src+2)) * (*(kerin+2));
            sum += (*(src+3)) * (*(kerin+3));
            sum += (*(src+4)) * (*(kerin+4));
            sum += (*(src+5)) * (*(kerin+5));
            sum += (*(src+6)) * (*(kerin+6));
            sum += (*(src+7)) * (*(kerin+7));
            (*(dest)) = sum;
            
 
            dest -= (dim - 8) ;
            kerin += dim;

        //l=1
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+8)) * (*(kerin));
                sum += (*(src+9)) * (*(kerin+1));
                sum += (*(src+10)) * (*(kerin+2));
                sum += (*(src+11)) * (*(kerin+3));
                sum += (*(src+12)) * (*(kerin+4));
                sum += (*(src+13)) * (*(kerin+5));
                sum += (*(src+14)) * (*(kerin+6));
                sum += (*(src+15)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+9)) * (*(kerin));
                sum += (*(src+10)) * (*(kerin+1));
                sum += (*(src+11)) * (*(kerin+2));
                sum += (*(src+12)) * (*(kerin+3));
                sum += (*(src+13)) * (*(kerin+4));
                sum += (*(src+14)) * (*(kerin+5));
                sum += (*(src+15)) * (*(kerin+6));
                sum += (*(src+16)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+10)) * (*(kerin));
                sum += (*(src+11)) * (*(kerin+1));
                sum += (*(src+12)) * (*(kerin+2));
                sum += (*(src+13)) * (*(kerin+3));
                sum += (*(src+14)) * (*(kerin+4));
                sum += (*(src+15)) * (*(kerin+5));
                sum += (*(src+16)) * (*(kerin+6));
                sum += (*(src+17)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+11)) * (*(kerin));
                sum += (*(src+12)) * (*(kerin+1));
                sum += (*(src+13)) * (*(kerin+2));
                sum += (*(src+14)) * (*(kerin+3));
                sum += (*(src+15)) * (*(kerin+4));
                sum += (*(src+16)) * (*(kerin+5));
                sum += (*(src+17)) * (*(kerin+6));
                sum += (*(src+18)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+12)) * (*(kerin));
                sum += (*(src+13)) * (*(kerin+1));
                sum += (*(src+14)) * (*(kerin+2));
                sum += (*(src+15)) * (*(kerin+3));
                sum += (*(src+16)) * (*(kerin+4));
                sum += (*(src+17)) * (*(kerin+5));
                sum += (*(src+18)) * (*(kerin+6));
                sum += (*(src+19)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+13)) * (*(kerin));
                sum += (*(src+14)) * (*(kerin+1));
                sum += (*(src+15)) * (*(kerin+2));
                sum += (*(src+16)) * (*(kerin+3));
                sum += (*(src+17)) * (*(kerin+4));
                sum += (*(src+18)) * (*(kerin+5));
                sum += (*(src+19)) * (*(kerin+6));
                sum += (*(src+20)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+14)) * (*(kerin));
                sum += (*(src+15)) * (*(kerin+1));
                sum += (*(src+16)) * (*(kerin+2));
                sum += (*(src+17)) * (*(kerin+3));
                sum += (*(src+18)) * (*(kerin+4));
                sum += (*(src+19)) * (*(kerin+5));
                sum += (*(src+20)) * (*(kerin+6));
                sum += (*(src+21)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+15)) * (*(kerin));
                sum += (*(src+16)) * (*(kerin+1));
                sum += (*(src+17)) * (*(kerin+2));
                sum += (*(src+18)) * (*(kerin+3));
                sum += (*(src+19)) * (*(kerin+4));
                sum += (*(src+20)) * (*(kerin+5));
                sum += (*(src+21)) * (*(kerin+6));
                sum += (*(src+22)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+8)) * (*(kerin));
            sum += (*(src+9)) * (*(kerin+1));
            sum += (*(src+10)) * (*(kerin+2));
            sum += (*(src+11)) * (*(kerin+3));
            sum += (*(src+12)) * (*(kerin+4));
            sum += (*(src+13)) * (*(kerin+5));
            sum += (*(src+14)) * (*(kerin+6));
            sum += (*(src+15)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
            
            dest -= (dim - 8) ;
            kerin += dim;
        //l=2
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+16)) * (*(kerin));
                sum += (*(src+17)) * (*(kerin+1));
                sum += (*(src+18)) * (*(kerin+2));
                sum += (*(src+19)) * (*(kerin+3));
                sum += (*(src+20)) * (*(kerin+4));
                sum += (*(src+21)) * (*(kerin+5));
                sum += (*(src+22)) * (*(kerin+6));
                sum += (*(src+23)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+17)) * (*(kerin));
                sum += (*(src+18)) * (*(kerin+1));
                sum += (*(src+19)) * (*(kerin+2));
                sum += (*(src+20)) * (*(kerin+3));
                sum += (*(src+21)) * (*(kerin+4));
                sum += (*(src+22)) * (*(kerin+5));
                sum += (*(src+23)) * (*(kerin+6));
                sum += (*(src+24)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+18)) * (*(kerin));
                sum += (*(src+19)) * (*(kerin+1));
                sum += (*(src+20)) * (*(kerin+2));
                sum += (*(src+21)) * (*(kerin+3));
                sum += (*(src+22)) * (*(kerin+4));
                sum += (*(src+23)) * (*(kerin+5));
                sum += (*(src+24)) * (*(kerin+6));
                sum += (*(src+25)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+19)) * (*(kerin));
                sum += (*(src+20)) * (*(kerin+1));
                sum += (*(src+21)) * (*(kerin+2));
                sum += (*(src+22)) * (*(kerin+3));
                sum += (*(src+23)) * (*(kerin+4));
                sum += (*(src+24)) * (*(kerin+5));
                sum += (*(src+25)) * (*(kerin+6));
                sum += (*(src+26)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+20)) * (*(kerin));
                sum += (*(src+21)) * (*(kerin+1));
                sum += (*(src+22)) * (*(kerin+2));
                sum += (*(src+23)) * (*(kerin+3));
                sum += (*(src+24)) * (*(kerin+4));
                sum += (*(src+25)) * (*(kerin+5));
                sum += (*(src+26)) * (*(kerin+6));
                sum += (*(src+27)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+21)) * (*(kerin));
                sum += (*(src+22)) * (*(kerin+1));
                sum += (*(src+23)) * (*(kerin+2));
                sum += (*(src+24)) * (*(kerin+3));
                sum += (*(src+25)) * (*(kerin+4));
                sum += (*(src+26)) * (*(kerin+5));
                sum += (*(src+27)) * (*(kerin+6));
                sum += (*(src+28)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+22)) * (*(kerin));
                sum += (*(src+23)) * (*(kerin+1));
                sum += (*(src+24)) * (*(kerin+2));
                sum += (*(src+25)) * (*(kerin+3));
                sum += (*(src+26)) * (*(kerin+4));
                sum += (*(src+27)) * (*(kerin+5));
                sum += (*(src+28)) * (*(kerin+6));
                sum += (*(src+29)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+23)) * (*(kerin));
                sum += (*(src+24)) * (*(kerin+1));
                sum += (*(src+25)) * (*(kerin+2));
                sum += (*(src+26)) * (*(kerin+3));
                sum += (*(src+27)) * (*(kerin+4));
                sum += (*(src+28)) * (*(kerin+5));
                sum += (*(src+29)) * (*(kerin+6));
                sum += (*(src+30)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+16)) * (*(kerin));
            sum += (*(src+17)) * (*(kerin+1));
            sum += (*(src+18)) * (*(kerin+2));
            sum += (*(src+19)) * (*(kerin+3));
            sum += (*(src+20)) * (*(kerin+4));
            sum += (*(src+21)) * (*(kerin+5));
            sum += (*(src+22)) * (*(kerin+6));
            sum += (*(src+23)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
            //src += 24;
            dest -= (dim - 8) ;
            kerin += dim;
        //l=3
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+24)) * (*(kerin));
                sum += (*(src+25)) * (*(kerin+1));
                sum += (*(src+26)) * (*(kerin+2));
                sum += (*(src+27)) * (*(kerin+3));
                sum += (*(src+28)) * (*(kerin+4));
                sum += (*(src+29)) * (*(kerin+5));
                sum += (*(src+30)) * (*(kerin+6));
                sum += (*(src+31)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+25)) * (*(kerin));
                sum += (*(src+26)) * (*(kerin+1));
                sum += (*(src+27)) * (*(kerin+2));
                sum += (*(src+28)) * (*(kerin+3));
                sum += (*(src+29)) * (*(kerin+4));
                sum += (*(src+30)) * (*(kerin+5));
                sum += (*(src+31)) * (*(kerin+6));
                sum += (*(src+32)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+26)) * (*(kerin));
                sum += (*(src+27)) * (*(kerin+1));
                sum += (*(src+28)) * (*(kerin+2));
                sum += (*(src+29)) * (*(kerin+3));
                sum += (*(src+30)) * (*(kerin+4));
                sum += (*(src+31)) * (*(kerin+5));
                sum += (*(src+32)) * (*(kerin+6));
                sum += (*(src+33)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+27)) * (*(kerin));
                sum += (*(src+28)) * (*(kerin+1));
                sum += (*(src+29)) * (*(kerin+2));
                sum += (*(src+30)) * (*(kerin+3));
                sum += (*(src+31)) * (*(kerin+4));
                sum += (*(src+32)) * (*(kerin+5));
                sum += (*(src+33)) * (*(kerin+6));
                sum += (*(src+34)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+28)) * (*(kerin));
                sum += (*(src+29)) * (*(kerin+1));
                sum += (*(src+30)) * (*(kerin+2));
                sum += (*(src+31)) * (*(kerin+3));
                sum += (*(src+32)) * (*(kerin+4));
                sum += (*(src+33)) * (*(kerin+5));
                sum += (*(src+34)) * (*(kerin+6));
                sum += (*(src+35)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+29)) * (*(kerin));
                sum += (*(src+30)) * (*(kerin+1));
                sum += (*(src+31)) * (*(kerin+2));
                sum += (*(src+32)) * (*(kerin+3));
                sum += (*(src+33)) * (*(kerin+4));
                sum += (*(src+34)) * (*(kerin+5));
                sum += (*(src+35)) * (*(kerin+6));
                sum += (*(src+36)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+30)) * (*(kerin));
                sum += (*(src+31)) * (*(kerin+1));
                sum += (*(src+32)) * (*(kerin+2));
                sum += (*(src+33)) * (*(kerin+3));
                sum += (*(src+34)) * (*(kerin+4));
                sum += (*(src+35)) * (*(kerin+5));
                sum += (*(src+36)) * (*(kerin+6));
                sum += (*(src+37)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+31)) * (*(kerin));
                sum += (*(src+32)) * (*(kerin+1));
                sum += (*(src+33)) * (*(kerin+2));
                sum += (*(src+34)) * (*(kerin+3));
                sum += (*(src+35)) * (*(kerin+4));
                sum += (*(src+36)) * (*(kerin+5));
                sum += (*(src+37)) * (*(kerin+6));
                sum += (*(src+38)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+24)) * (*(kerin));
            sum += (*(src+25)) * (*(kerin+1));
            sum += (*(src+26)) * (*(kerin+2));
            sum += (*(src+27)) * (*(kerin+3));
            sum += (*(src+28)) * (*(kerin+4));
            sum += (*(src+29)) * (*(kerin+5));
            sum += (*(src+30)) * (*(kerin+6));
            sum += (*(src+31)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
            
            dest -= (dim - 8) ;
            kerin += dim;

        //l=4
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+32)) * (*(kerin));
                sum += (*(src+33)) * (*(kerin+1));
                sum += (*(src+34)) * (*(kerin+2));
                sum += (*(src+35)) * (*(kerin+3));
                sum += (*(src+36)) * (*(kerin+4));
                sum += (*(src+37)) * (*(kerin+5));
                sum += (*(src+38)) * (*(kerin+6));
                sum += (*(src+39)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+33)) * (*(kerin));
                sum += (*(src+34)) * (*(kerin+1));
                sum += (*(src+35)) * (*(kerin+2));
                sum += (*(src+36)) * (*(kerin+3));
                sum += (*(src+37)) * (*(kerin+4));
                sum += (*(src+38)) * (*(kerin+5));
                sum += (*(src+39)) * (*(kerin+6));
                sum += (*(src+40)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+34)) * (*(kerin));
                sum += (*(src+35)) * (*(kerin+1));
                sum += (*(src+36)) * (*(kerin+2));
                sum += (*(src+37)) * (*(kerin+3));
                sum += (*(src+38)) * (*(kerin+4));
                sum += (*(src+39)) * (*(kerin+5));
                sum += (*(src+40)) * (*(kerin+6));
                sum += (*(src+41)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+35)) * (*(kerin));
                sum += (*(src+36)) * (*(kerin+1));
                sum += (*(src+37)) * (*(kerin+2));
                sum += (*(src+38)) * (*(kerin+3));
                sum += (*(src+39)) * (*(kerin+4));
                sum += (*(src+40)) * (*(kerin+5));
                sum += (*(src+41)) * (*(kerin+6));
                sum += (*(src+42)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+36)) * (*(kerin));
                sum += (*(src+37)) * (*(kerin+1));
                sum += (*(src+38)) * (*(kerin+2));
                sum += (*(src+39)) * (*(kerin+3));
                sum += (*(src+40)) * (*(kerin+4));
                sum += (*(src+41)) * (*(kerin+5));
                sum += (*(src+42)) * (*(kerin+6));
                sum += (*(src+43)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+37)) * (*(kerin));
                sum += (*(src+38)) * (*(kerin+1));
                sum += (*(src+39)) * (*(kerin+2));
                sum += (*(src+40)) * (*(kerin+3));
                sum += (*(src+41)) * (*(kerin+4));
                sum += (*(src+42)) * (*(kerin+5));
                sum += (*(src+43)) * (*(kerin+6));
                sum += (*(src+44)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+38)) * (*(kerin));
                sum += (*(src+39)) * (*(kerin+1));
                sum += (*(src+40)) * (*(kerin+2));
                sum += (*(src+41)) * (*(kerin+3));
                sum += (*(src+42)) * (*(kerin+4));
                sum += (*(src+43)) * (*(kerin+5));
                sum += (*(src+44)) * (*(kerin+6));
                sum += (*(src+45)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+39)) * (*(kerin));
                sum += (*(src+40)) * (*(kerin+1));
                sum += (*(src+41)) * (*(kerin+2));
                sum += (*(src+42)) * (*(kerin+3));
                sum += (*(src+43)) * (*(kerin+4));
                sum += (*(src+44)) * (*(kerin+5));
                sum += (*(src+45)) * (*(kerin+6));
                sum += (*(src+46)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+32)) * (*(kerin));
            sum += (*(src+33)) * (*(kerin+1));
            sum += (*(src+34)) * (*(kerin+2));
            sum += (*(src+35)) * (*(kerin+3));
            sum += (*(src+36)) * (*(kerin+4));
            sum += (*(src+37)) * (*(kerin+5));
            sum += (*(src+38)) * (*(kerin+6));
            sum += (*(src+39)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
            
            dest -= (dim - 8) ;
            kerin += dim;
        //l=5
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+40)) * (*(kerin));
                sum += (*(src+41)) * (*(kerin+1));
                sum += (*(src+42)) * (*(kerin+2));
                sum += (*(src+43)) * (*(kerin+3));
                sum += (*(src+44)) * (*(kerin+4));
                sum += (*(src+45)) * (*(kerin+5));
                sum += (*(src+46)) * (*(kerin+6));
                sum += (*(src+47)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+41)) * (*(kerin));
                sum += (*(src+42)) * (*(kerin+1));
                sum += (*(src+43)) * (*(kerin+2));
                sum += (*(src+44)) * (*(kerin+3));
                sum += (*(src+45)) * (*(kerin+4));
                sum += (*(src+46)) * (*(kerin+5));
                sum += (*(src+47)) * (*(kerin+6));
                sum += (*(src+48)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+42)) * (*(kerin));
                sum += (*(src+43)) * (*(kerin+1));
                sum += (*(src+44)) * (*(kerin+2));
                sum += (*(src+45)) * (*(kerin+3));
                sum += (*(src+46)) * (*(kerin+4));
                sum += (*(src+47)) * (*(kerin+5));
                sum += (*(src+48)) * (*(kerin+6));
                sum += (*(src+49)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+43)) * (*(kerin));
                sum += (*(src+44)) * (*(kerin+1));
                sum += (*(src+45)) * (*(kerin+2));
                sum += (*(src+46)) * (*(kerin+3));
                sum += (*(src+47)) * (*(kerin+4));
                sum += (*(src+48)) * (*(kerin+5));
                sum += (*(src+49)) * (*(kerin+6));
                sum += (*(src+50)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+44)) * (*(kerin));
                sum += (*(src+45)) * (*(kerin+1));
                sum += (*(src+46)) * (*(kerin+2));
                sum += (*(src+47)) * (*(kerin+3));
                sum += (*(src+48)) * (*(kerin+4));
                sum += (*(src+49)) * (*(kerin+5));
                sum += (*(src+50)) * (*(kerin+6));
                sum += (*(src+51)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+45)) * (*(kerin));
                sum += (*(src+46)) * (*(kerin+1));
                sum += (*(src+47)) * (*(kerin+2));
                sum += (*(src+48)) * (*(kerin+3));
                sum += (*(src+49)) * (*(kerin+4));
                sum += (*(src+50)) * (*(kerin+5));
                sum += (*(src+51)) * (*(kerin+6));
                sum += (*(src+52)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+46)) * (*(kerin));
                sum += (*(src+47)) * (*(kerin+1));
                sum += (*(src+48)) * (*(kerin+2));
                sum += (*(src+49)) * (*(kerin+3));
                sum += (*(src+50)) * (*(kerin+4));
                sum += (*(src+51)) * (*(kerin+5));
                sum += (*(src+52)) * (*(kerin+6));
                sum += (*(src+53)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+47)) * (*(kerin));
                sum += (*(src+48)) * (*(kerin+1));
                sum += (*(src+49)) * (*(kerin+2));
                sum += (*(src+50)) * (*(kerin+3));
                sum += (*(src+51)) * (*(kerin+4));
                sum += (*(src+52)) * (*(kerin+5));
                sum += (*(src+53)) * (*(kerin+6));
                sum += (*(src+54)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+40)) * (*(kerin));
            sum += (*(src+41)) * (*(kerin+1));
            sum += (*(src+42)) * (*(kerin+2));
            sum += (*(src+43)) * (*(kerin+3));
            sum += (*(src+44)) * (*(kerin+4));
            sum += (*(src+45)) * (*(kerin+5));
            sum += (*(src+46)) * (*(kerin+6));
            sum += (*(src+47)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
            
            dest -= (dim - 8) ;
            kerin += dim;
        //l=6
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+48)) * (*(kerin));
                sum += (*(src+49)) * (*(kerin+1));
                sum += (*(src+50)) * (*(kerin+2));
                sum += (*(src+51)) * (*(kerin+3));
                sum += (*(src+52)) * (*(kerin+4));
                sum += (*(src+53)) * (*(kerin+5));
                sum += (*(src+54)) * (*(kerin+6));
                sum += (*(src+55)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+49)) * (*(kerin));
                sum += (*(src+50)) * (*(kerin+1));
                sum += (*(src+51)) * (*(kerin+2));
                sum += (*(src+52)) * (*(kerin+3));
                sum += (*(src+53)) * (*(kerin+4));
                sum += (*(src+54)) * (*(kerin+5));
                sum += (*(src+55)) * (*(kerin+6));
                sum += (*(src+56)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+50)) * (*(kerin));
                sum += (*(src+51)) * (*(kerin+1));
                sum += (*(src+52)) * (*(kerin+2));
                sum += (*(src+53)) * (*(kerin+3));
                sum += (*(src+54)) * (*(kerin+4));
                sum += (*(src+55)) * (*(kerin+5));
                sum += (*(src+56)) * (*(kerin+6));
                sum += (*(src+57)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+51)) * (*(kerin));
                sum += (*(src+52)) * (*(kerin+1));
                sum += (*(src+53)) * (*(kerin+2));
                sum += (*(src+54)) * (*(kerin+3));
                sum += (*(src+55)) * (*(kerin+4));
                sum += (*(src+56)) * (*(kerin+5));
                sum += (*(src+57)) * (*(kerin+6));
                sum += (*(src+58)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+52)) * (*(kerin));
                sum += (*(src+53)) * (*(kerin+1));
                sum += (*(src+54)) * (*(kerin+2));
                sum += (*(src+55)) * (*(kerin+3));
                sum += (*(src+56)) * (*(kerin+4));
                sum += (*(src+57)) * (*(kerin+5));
                sum += (*(src+58)) * (*(kerin+6));
                sum += (*(src+59)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+53)) * (*(kerin));
                sum += (*(src+54)) * (*(kerin+1));
                sum += (*(src+55)) * (*(kerin+2));
                sum += (*(src+56)) * (*(kerin+3));
                sum += (*(src+57)) * (*(kerin+4));
                sum += (*(src+58)) * (*(kerin+5));
                sum += (*(src+59)) * (*(kerin+6));
                sum += (*(src+60)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+54)) * (*(kerin));
                sum += (*(src+55)) * (*(kerin+1));
                sum += (*(src+56)) * (*(kerin+2));
                sum += (*(src+57)) * (*(kerin+3));
                sum += (*(src+58)) * (*(kerin+4));
                sum += (*(src+59)) * (*(kerin+5));
                sum += (*(src+60)) * (*(kerin+6));
                sum += (*(src+61)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+55)) * (*(kerin));
                sum += (*(src+56)) * (*(kerin+1));
                sum += (*(src+57)) * (*(kerin+2));
                sum += (*(src+58)) * (*(kerin+3));
                sum += (*(src+59)) * (*(kerin+4));
                sum += (*(src+60)) * (*(kerin+5));
                sum += (*(src+61)) * (*(kerin+6));
                sum += (*(src+62)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+48)) * (*(kerin));
            sum += (*(src+49)) * (*(kerin+1));
            sum += (*(src+50)) * (*(kerin+2));
            sum += (*(src+51)) * (*(kerin+3));
            sum += (*(src+52)) * (*(kerin+4));
            sum += (*(src+53)) * (*(kerin+5));
            sum += (*(src+54)) * (*(kerin+6));
            sum += (*(src+55)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
            
            dest -= (dim - 8) ;
            kerin += dim;
        //l=7
            for(i = 0; i < dm15; i+=8){
                
                sum=0;
                sum += (*(src+56)) * (*(kerin));
                sum += (*(src+57)) * (*(kerin+1));
                sum += (*(src+58)) * (*(kerin+2));
                sum += (*(src+59)) * (*(kerin+3));
                sum += (*(src+60)) * (*(kerin+4));
                sum += (*(src+61)) * (*(kerin+5));
                sum += (*(src+62)) * (*(kerin+6));
                sum += (*(src+63)) * (*(kerin+7));
                (*(dest)) += sum;

                
                sum=0;
                sum += (*(src+57)) * (*(kerin));
                sum += (*(src+58)) * (*(kerin+1));
                sum += (*(src+59)) * (*(kerin+2));
                sum += (*(src+60)) * (*(kerin+3));
                sum += (*(src+61)) * (*(kerin+4));
                sum += (*(src+62)) * (*(kerin+5));
                sum += (*(src+63)) * (*(kerin+6));
                sum += (*(src+64)) * (*(kerin+7));
                (*(dest+1)) += sum;
                
               
                sum=0;
                sum += (*(src+58)) * (*(kerin));
                sum += (*(src+59)) * (*(kerin+1));
                sum += (*(src+60)) * (*(kerin+2));
                sum += (*(src+61)) * (*(kerin+3));
                sum += (*(src+62)) * (*(kerin+4));
                sum += (*(src+63)) * (*(kerin+5));
                sum += (*(src+64)) * (*(kerin+6));
                sum += (*(src+65)) * (*(kerin+7));
                (*(dest+2)) += sum;
                
                
                sum=0;
                sum += (*(src+59)) * (*(kerin));
                sum += (*(src+60)) * (*(kerin+1));
                sum += (*(src+61)) * (*(kerin+2));
                sum += (*(src+62)) * (*(kerin+3));
                sum += (*(src+63)) * (*(kerin+4));
                sum += (*(src+64)) * (*(kerin+5));
                sum += (*(src+65)) * (*(kerin+6));
                sum += (*(src+66)) * (*(kerin+7));
                (*(dest+3)) += sum;

              
                sum=0;
                sum += (*(src+60)) * (*(kerin));
                sum += (*(src+61)) * (*(kerin+1));
                sum += (*(src+62)) * (*(kerin+2));
                sum += (*(src+63)) * (*(kerin+3));
                sum += (*(src+64)) * (*(kerin+4));
                sum += (*(src+65)) * (*(kerin+5));
                sum += (*(src+66)) * (*(kerin+6));
                sum += (*(src+67)) * (*(kerin+7));
                (*(dest+4)) += sum;
                
            
                sum=0;
                sum += (*(src+61)) * (*(kerin));
                sum += (*(src+62)) * (*(kerin+1));
                sum += (*(src+63)) * (*(kerin+2));
                sum += (*(src+64)) * (*(kerin+3));
                sum += (*(src+65)) * (*(kerin+4));
                sum += (*(src+66)) * (*(kerin+5));
                sum += (*(src+67)) * (*(kerin+6));
                sum += (*(src+68)) * (*(kerin+7));
                (*(dest+5)) += sum;
                
            
                sum=0;
                sum += (*(src+62)) * (*(kerin));
                sum += (*(src+63)) * (*(kerin+1));
                sum += (*(src+64)) * (*(kerin+2));
                sum += (*(src+65)) * (*(kerin+3));
                sum += (*(src+66)) * (*(kerin+4));
                sum += (*(src+67)) * (*(kerin+5));
                sum += (*(src+68)) * (*(kerin+6));
                sum += (*(src+69)) * (*(kerin+7));
                (*(dest+6)) += sum;
                
             
                sum=0;
                sum += (*(src+63)) * (*(kerin));
                sum += (*(src+64)) * (*(kerin+1));
                sum += (*(src+65)) * (*(kerin+2));
                sum += (*(src+66)) * (*(kerin+3));
                sum += (*(src+67)) * (*(kerin+4));
                sum += (*(src+68)) * (*(kerin+5));
                sum += (*(src+69)) * (*(kerin+6));
                sum += (*(src+70)) * (*(kerin+7));
                (*(dest+7)) += sum;
                dest+=8;
                src+=8;
            }
            
            sum=0;
            sum += (*(src+56)) * (*(kerin));
            sum += (*(src+57)) * (*(kerin+1));
            sum += (*(src+58)) * (*(kerin+2));
            sum += (*(src+59)) * (*(kerin+3));
            sum += (*(src+60)) * (*(kerin+4));
            sum += (*(src+61)) * (*(kerin+5));
            sum += (*(src+62)) * (*(kerin+6));
            sum += (*(src+63)) * (*(kerin+7));
            (*(dest)) += sum;
            
            
        //8l end
            
    dest += 8 ;
    kerin += dim;
    src =src + 64 - (7*(dim)); 
    }         
        
}

char naive_convjilk_descr[] = "naive_conv: Naive baseline implementation jilk";
void naive_convjilk(int dim,int *src, int *ker,int *dest) {
    int i,j,l;
    int  jdim;
    int sum;
    int *destin, *srcin, *kerin;
    

    jdim = 0;
    destin = dest;
    for(j = 0; j < dim-7; j++){
        
        srcin = src+ jdim;
        
        for(i = 0; i < dim-7; i++){
            *destin = 0;
            kerin = ker;
            

            sum=0; 

            for(l = 0; l < 8; l++){
                
            sum += (*(srcin)) * (*(kerin));sum += (*(srcin+1)) * (*(kerin+1)) ;sum += (*(srcin+2)) * (*(kerin+2));
            sum += (*(srcin+3)) * (*(kerin+3)) ;sum += (*(srcin+4)) * (*(kerin+4));sum += (*(srcin+5)) * (*(kerin+5));
            sum += (*(srcin+6)) * (*(kerin+6)) ;sum += (*(srcin+7)) * (*(kerin+7));
            kerin = kerin +dim;srcin = srcin + dim;
            }


            (*(destin)) += sum;
            srcin = srcin + 1 - (8*dim);

        destin++;
        }
    jdim+=dim;
    destin = destin+7;

    }         
        
}

char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim,int *src, int *ker,int *dest) {

    int j,l;

    int sum;
    int *destin;
    int *srcin;
    int *kerin;
    int dimm7 = dim-7;

   


    for(j=0; j<dimm7; j++){

        kerin = ker;
        srcin=src;
        destin = dest;

            for(; destin < dest+dimm7 ; ){

                sum=0;
                sum += (*(srcin)) * (*(kerin));
                sum += (*(srcin+1)) * (*(kerin+1));
                sum += (*(srcin+2)) * (*(kerin+2));
                sum += (*(srcin+3)) * (*(kerin+3));
                sum += (*(srcin+4)) * (*(kerin+4));
                sum += (*(srcin+5)) * (*(kerin+5));
                sum += (*(srcin+6)) * (*(kerin+6));
                sum += (*(srcin+7)) * (*(kerin+7));

                (*(destin)) = sum;

                sum=0;
                sum += (*(srcin+1)) * (*(kerin));
                sum += (*(srcin+2)) * (*(kerin+1));
                sum += (*(srcin+3)) * (*(kerin+2));
                sum += (*(srcin+4)) * (*(kerin+3));
                sum += (*(srcin+5)) * (*(kerin+4));
                sum += (*(srcin+6)) * (*(kerin+5));
                sum += (*(srcin+7)) * (*(kerin+6));
                sum += (*(srcin+8)) * (*(kerin+7));

                (*(destin+1)) = sum;

                sum=0;
                sum += (*(srcin+2)) * (*(kerin));
                sum += (*(srcin+3)) * (*(kerin+1));
                sum += (*(srcin+4)) * (*(kerin+2));
                sum += (*(srcin+5)) * (*(kerin+3));
                sum += (*(srcin+6)) * (*(kerin+4));
                sum += (*(srcin+7)) * (*(kerin+5));
                sum += (*(srcin+8)) * (*(kerin+6));
                sum += (*(srcin+9)) * (*(kerin+7));

                (*(destin+2)) = sum;

                sum=0;
                sum += (*(srcin+3)) * (*(kerin));
                sum += (*(srcin+4)) * (*(kerin+1));
                sum += (*(srcin+5)) * (*(kerin+2));
                sum += (*(srcin+6)) * (*(kerin+3));
                sum += (*(srcin+7)) * (*(kerin+4));
                sum += (*(srcin+8)) * (*(kerin+5));
                sum += (*(srcin+9)) * (*(kerin+6));
                sum += (*(srcin+10)) * (*(kerin+7));

                (*(destin+3)) = sum;

                sum=0;
                sum += (*(srcin+4)) * (*(kerin));
                sum += (*(srcin+5)) * (*(kerin+1));
                sum += (*(srcin+6)) * (*(kerin+2));
                sum += (*(srcin+7)) * (*(kerin+3));
                sum += (*(srcin+8)) * (*(kerin+4));
                sum += (*(srcin+9)) * (*(kerin+5));
                sum += (*(srcin+10)) * (*(kerin+6));
                sum += (*(srcin+11)) * (*(kerin+7));

                (*(destin+4)) = sum;

                sum=0;
                sum += (*(srcin+5)) * (*(kerin));
                sum += (*(srcin+6)) * (*(kerin+1));
                sum += (*(srcin+7)) * (*(kerin+2));
                sum += (*(srcin+8)) * (*(kerin+3));
                sum += (*(srcin+9)) * (*(kerin+4));
                sum += (*(srcin+10)) * (*(kerin+5));
                sum += (*(srcin+11)) * (*(kerin+6));
                sum += (*(srcin+12)) * (*(kerin+7));

                (*(destin+5)) = sum;

                sum=0;
                sum += (*(srcin+6)) * (*(kerin));
                sum += (*(srcin+7)) * (*(kerin+1));
                sum += (*(srcin+8)) * (*(kerin+2));
                sum += (*(srcin+9)) * (*(kerin+3));
                sum += (*(srcin+10)) * (*(kerin+4));
                sum += (*(srcin+11)) * (*(kerin+5));
                sum += (*(srcin+12)) * (*(kerin+6));
                sum += (*(srcin+13)) * (*(kerin+7));

                (*(destin+6)) = sum;

                sum=0;
                sum += (*(srcin+7)) * (*(kerin));
                sum += (*(srcin+8)) * (*(kerin+1));
                sum += (*(srcin+9)) * (*(kerin+2));
                sum += (*(srcin+10)) * (*(kerin+3));
                sum += (*(srcin+11)) * (*(kerin+4));
                sum += (*(srcin+12)) * (*(kerin+5));
                sum += (*(srcin+13)) * (*(kerin+6));
                sum += (*(srcin+14)) * (*(kerin+7));

                (*(destin+7)) = sum;



                destin+=8;
                srcin+=8;

            }
        kerin+=dim;
        destin-=dim;
        



        for(l = 1; l < 8; l++){
            
            for(; destin < dest+dimm7 ; ){
                

                sum=0;
                sum += (*(srcin)) * (*(kerin));
                sum += (*(srcin+1)) * (*(kerin+1));
                sum += (*(srcin+2)) * (*(kerin+2));
                sum += (*(srcin+3)) * (*(kerin+3));
                sum += (*(srcin+4)) * (*(kerin+4));
                sum += (*(srcin+5)) * (*(kerin+5));
                sum += (*(srcin+6)) * (*(kerin+6));
                sum += (*(srcin+7)) * (*(kerin+7));

                (*(destin)) += sum;

                sum=0;
                sum += (*(srcin+1)) * (*(kerin));
                sum += (*(srcin+2)) * (*(kerin+1));
                sum += (*(srcin+3)) * (*(kerin+2));
                sum += (*(srcin+4)) * (*(kerin+3));
                sum += (*(srcin+5)) * (*(kerin+4));
                sum += (*(srcin+6)) * (*(kerin+5));
                sum += (*(srcin+7)) * (*(kerin+6));
                sum += (*(srcin+8)) * (*(kerin+7));

                (*(destin+1)) += sum;

                sum=0;
                sum += (*(srcin+2)) * (*(kerin));
                sum += (*(srcin+3)) * (*(kerin+1));
                sum += (*(srcin+4)) * (*(kerin+2));
                sum += (*(srcin+5)) * (*(kerin+3));
                sum += (*(srcin+6)) * (*(kerin+4));
                sum += (*(srcin+7)) * (*(kerin+5));
                sum += (*(srcin+8)) * (*(kerin+6));
                sum += (*(srcin+9)) * (*(kerin+7));

                (*(destin+2)) += sum;

                sum=0;
                sum += (*(srcin+3)) * (*(kerin));
                sum += (*(srcin+4)) * (*(kerin+1));
                sum += (*(srcin+5)) * (*(kerin+2));
                sum += (*(srcin+6)) * (*(kerin+3));
                sum += (*(srcin+7)) * (*(kerin+4));
                sum += (*(srcin+8)) * (*(kerin+5));
                sum += (*(srcin+9)) * (*(kerin+6));
                sum += (*(srcin+10)) * (*(kerin+7));

                (*(destin+3)) += sum;

                sum=0;
                sum += (*(srcin+4)) * (*(kerin));
                sum += (*(srcin+5)) * (*(kerin+1));
                sum += (*(srcin+6)) * (*(kerin+2));
                sum += (*(srcin+7)) * (*(kerin+3));
                sum += (*(srcin+8)) * (*(kerin+4));
                sum += (*(srcin+9)) * (*(kerin+5));
                sum += (*(srcin+10)) * (*(kerin+6));
                sum += (*(srcin+11)) * (*(kerin+7));

                (*(destin+4)) += sum;

                sum=0;
                sum += (*(srcin+5)) * (*(kerin));
                sum += (*(srcin+6)) * (*(kerin+1));
                sum += (*(srcin+7)) * (*(kerin+2));
                sum += (*(srcin+8)) * (*(kerin+3));
                sum += (*(srcin+9)) * (*(kerin+4));
                sum += (*(srcin+10)) * (*(kerin+5));
                sum += (*(srcin+11)) * (*(kerin+6));
                sum += (*(srcin+12)) * (*(kerin+7));

                (*(destin+5)) += sum;

                sum=0;
                sum += (*(srcin+6)) * (*(kerin));
                sum += (*(srcin+7)) * (*(kerin+1));
                sum += (*(srcin+8)) * (*(kerin+2));
                sum += (*(srcin+9)) * (*(kerin+3));
                sum += (*(srcin+10)) * (*(kerin+4));
                sum += (*(srcin+11)) * (*(kerin+5));
                sum += (*(srcin+12)) * (*(kerin+6));
                sum += (*(srcin+13)) * (*(kerin+7));

                (*(destin+6)) += sum;

                sum=0;
                sum += (*(srcin+7)) * (*(kerin));
                sum += (*(srcin+8)) * (*(kerin+1));
                sum += (*(srcin+9)) * (*(kerin+2));
                sum += (*(srcin+10)) * (*(kerin+3));
                sum += (*(srcin+11)) * (*(kerin+4));
                sum += (*(srcin+12)) * (*(kerin+5));
                sum += (*(srcin+13)) * (*(kerin+6));
                sum += (*(srcin+14)) * (*(kerin+7));

                (*(destin+7)) += sum;



                destin+=8;
                srcin+=8;

            }
        kerin+=dim;
        destin-=dim;
        }
        dest+=dim;
        src+=dim;
    }
                 
}


 
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dest) 
{
 
    int i,j;
    int idim;
    int cl;
    int cc;
    int r;
    int imcldim;
    int cldim;

    for(i=0; i< dim; i++){
        idim = i*dim;
        for(j=0;j<dim;j++){
            dest[idim+j] = 0;    
        }
        
    }
        
    for(i=0; i<dim-8; i++){
        idim = i*dim;
        for(cl=0; cl<=min( 7, i ); cl++){
            imcldim = (i-cl)*dim;
            cldim = cl*dim;
            for(j=0; j<dim; j++){

                r = src[idim+j];
                
                for(cc=0; cc<=min(7, j) ; cc++){
                    
                    dest[imcldim+(j-cc)] += r * ker[cldim+cc];
                }
                
            }
            
        }
        
    }

  

    for(i=dim-8; i<dim; i++){
        idim = i*dim;        
        for(cl=7; cl>=max(0,i-dim+8); cl--){
            imcldim = (i-cl)*dim;
            cldim = cl*dim;
            for(j=0; j<dim; j++) {

                r = src[idim+j];
                
                for(cc=7 ; cc>=max(0,j-dim+8) ; cc--){             
                    dest[imcldim+(j-cc)] += r * ker[cldim+cc];           
                }
            }         
        }
    }


}
 /*
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dest) 
{
 
    int i,j,k,l;
    int idim, jdim;
    int cl;
    int cc;


    for(i=0; i< dim; i++){
        for(j=0;j<dim;j++){
            dest[i*dim+j] = 0;    
        }
        
    }
        
    for(i=0; i<dim-8; i++){
        idim = i*dim;
        for(j=0; j<dim; j++){
            jdim = j*dim; 
            for(cl=0; cl<=min( 7, i ); cl++){               
                for(cc=0; cc<=min(7, j) ; cc++){
                    dest[(i-cl)*dim+(j-cc)] += src[idim+j] * ker[cl*dim+cc];                     
                }
            }         
        }
    }

        

    for(i=dim-8; i<dim; i++){
        idim = i*dim;        
        for(j=0; j<dim; j++){
            jdim = j*dim; 
            for(cl=7; cl>=max(0,i-dim+8); cl--){
                for(cc=7 ; cc>=max(0,j-dim+8) ; cc--){             
                    dest[(i-cl)*dim+(j-cc)] += src[idim+j] * ker[cl*dim+cc];           
                }
            }         
        }
    }

}
*/
/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_conv_functions() {

    //add_conv_function(&convolution, convolution_descr);   
    //add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&naive_convbasesondeneme, naive_convbasesondeneme_descr);
    add_conv_function(&naive_convijlk, naive_convijlk_descr); 
    add_conv_function(&naive_convijlkcrazyunroll, naive_convijlkcrazyunroll_descr);   
    add_conv_function(&naive_convjilk, naive_convjilk_descr);   
    /* ... Register additional test functions here */
}




/***************
 * MATRIX MULTIP KERNEL
 ***************/

/******************************************************
 * Your different versions of the matrix multiplications  go here
 ******************************************************/

/* 
 * naive_matrix_multiplication - The naive baseline version of matrix multiplication 
 */
char naive_matrix_multiplication_descr[] = "Naive_matrix_multiplication: Naive baseline implementation";
void naive_matrix_multiplication(int dim,int *src, int *src2,int *dst) {
    int i,j,k;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {
            dst[j*dim+i]=0;
            for(k = 0; k < dim; k++) 
                dst[j*dim+i] = dst[j*dim+i] + src[j*dim+k]*src2[i+k*dim];
        }    
}


char matrix_multiplication_block_descr[] = "Matrix mult with blocking";
void matrix_multiplication_blocking(int n,int *a, int *b,int *dest) 
{


    int i,j,k;
    int in;
    int  i1n;
    int sum;
    int bs=10;
    int i1,j1,k1;
    
    for(i = 0; i < n; i++){
        in = i*n;
        for(j = 0; j < n; j++) {
            dest[in+j]=0;
        }  
    }

    for(i = 0; i < n; i+=bs)
        for(j = 0; j < n; j+=bs) {
            for(k = 0; k < n; k+=bs) 
                /* B*B mini matrix mult */
                for(i1=i ; i1 < i+bs ; i1++)
                    for(j1=j ; j1 < j+bs ; j1++){
                        sum=0;
                        i1n = i1*n;
                        
                        for( k1=k ; k1<k+bs ; k1++){

                            sum += a[i1n+k1]*b[k1*n+j1];
                        }
                        dest[i1*n+j1] += sum;
                    }


                
        
     }    
}



char blockreuse_descr[] = "Matrix mult with block reuse no unroll";
void blockreuse(int n,int *A, int *B, int *C )
{ 
    int i, j, k, ii, jj, kk, Aik, bs = 32;
    
    int in, kn;

    for(i = 0; i < n; i++){
        in = i*n;
        for(j = 0; j < n; j++) {
            C[in+j]=0;
        }  
    }
    
    for(ii = 0; ii < n; ii += bs)
        for(kk = 0; kk < n; kk += bs)
            for(jj = 0; jj < n; jj += bs)
                for(i = ii; i < ii+bs; i++)
                    for(k = kk; k < kk+bs; k++)
                    {
                        in= i*n;
                        kn = k*n;
                        Aik = A[in+k];
                        
                        for(j = jj; j < jj+bs; j++)
                            C[in+j] += Aik * B[kn+j];     
                    }                   
}



char unroll16_descr[] = "Matrix mult blocking, reuse, unroll 16";
void unroll16(int n,int *A, int *B, int *C )
{ 
    int i, j, k, ii, jj, kk, Aik, bs = 128;

    int in, kn;

    int iipbs,jjpbs,kkpbs;



    for(i = 0; i < n; i++){
        in = i*n;
        for(j = 0; j < n; j++) {
            C[in+j]=0;
        }  
    }

    for(ii = 0; ii < n; ii += bs)
        for(kk = 0; kk < n; kk += bs)
            for(jj = 0; jj < n; jj += bs){
             
                iipbs = min(n, ii+bs);
                for(i = ii; i < iipbs; i++){
             
                    kkpbs = min(n, kk+bs);
                    for(k = kk; k < kkpbs ; k++)
                    {
                        in = i*n;
                        kn = k*n;
                        Aik = A[in+k];
                        jjpbs = min(n, jj+bs );

                        for(j = jj; j < jjpbs; j+=16)
                        {
                            C[in+j] += Aik * B[kn+j];
                            C[in+j+1] += Aik * B[kn+j+1];     
                            C[in+j+2] += Aik * B[kn+j+2]; 
                            C[in+j+3] += Aik * B[kn+j+3]; 
                            C[in+j+4] += Aik * B[kn+j+4];     
                            C[in+j+5] += Aik * B[kn+j+5]; 
                            C[in+j+6] += Aik * B[kn+j+6]; 
                            C[in+j+7] += Aik * B[kn+j+7];
                            C[in+j+8] += Aik * B[kn+j+8];     
                            C[in+j+9] += Aik * B[kn+j+9]; 
                            C[in+j+10] += Aik * B[kn+j+10];   
                            C[in+j+11] += Aik * B[kn+j+11];       
                            C[in+j+12] += Aik * B[kn+j+12];   
                            C[in+j+13] += Aik * B[kn+j+13];   
                            C[in+j+14] += Aik * B[kn+j+14];   
                            C[in+j+15] += Aik * B[kn+j+15];
                    
                        }

                    }                   
                }
            }   
}


char unroll32_descr[] = "Matrix mult with unroll 32";
void unroll32(int n,int *A, int *B, int *C )
{ 
    int i, j, k, ii, jj, kk, r, bs = 64;

    int in, kn;

    int iipbs,jjpbs,kkpbs;
    int* destin;
    int* src2in;
    


    int dim2 = n*n;
    destin = C;
    for(i=0;i <dim2; i+=8){
        
        *(destin)=0;
        *(destin+1)=0;
        *(destin+2)=0;
        *(destin+3)=0;
        *(destin+4)=0;
        *(destin+5)=0;
        *(destin+6)=0;
        *(destin+7)=0;
        destin+=8;
    }
    
    for(ii = 0; ii < n; ii += bs){
        

        for(kk = 0; kk < n; kk += bs){
            for(jj = 0; jj < n; jj += bs){
             
                iipbs = min(n, ii+bs);
                for(i = ii; i < iipbs; i++){
             
                    kkpbs = min(n, kk+bs);
                    for(k = kk; k < kkpbs ; k++)
                    {
                        in = i*n;
                        kn = k*n;
                        jjpbs = min(n, jj+bs );
                        r = A[in+k];
                        //fazlalik = jjpbs - 32;
                        for(j = jj; j < jjpbs; j+=32)
                        {

                            destin = C+in + j;
                            src2in = B+kn + j;

                            *destin += r*(*src2in);
                            *(destin+1) += r*(*(src2in+1));
                            *(destin+2) += r*(*(src2in+2));
                            *(destin+3) += r*(*(src2in+3));
                            *(destin+4) += r*(*(src2in+4));
                            *(destin+5) += r*(*(src2in+5));
                            *(destin+6) += r*(*(src2in+6));
                            *(destin+7) += r*(*(src2in+7));
                            *(destin+8) += r*(*(src2in+8));
                            *(destin+9) += r*(*(src2in+9));
                            *(destin+10) += r*(*(src2in+10));
                            *(destin+11) += r*(*(src2in+11));
                            *(destin+12) += r*(*(src2in+12));
                            *(destin+13) += r*(*(src2in+13));
                            *(destin+14) += r*(*(src2in+14));
                            *(destin+15) += r*(*(src2in+15));
                            *(destin+16) += r*(*(src2in+16));
                            *(destin+17) += r*(*(src2in+17));
                            *(destin+18) += r*(*(src2in+18));
                            *(destin+19) += r*(*(src2in+19));
                            *(destin+20) += r*(*(src2in+20));
                            *(destin+21) += r*(*(src2in+21));
                            *(destin+22) += r*(*(src2in+22));
                            *(destin+23) += r*(*(src2in+23));
                            *(destin+24) += r*(*(src2in+24));
                            *(destin+25) += r*(*(src2in+25));
                            *(destin+26) += r*(*(src2in+26));
                            *(destin+27) += r*(*(src2in+27));
                            *(destin+28) += r*(*(src2in+28));
                            *(destin+29) += r*(*(src2in+29));
                            *(destin+30) += r*(*(src2in+30));
                            *(destin+31) += r*(*(src2in+31));


                        }

                    }                   
                }
            }   
        }
    }
}




char matrix_multiplication16_descr[] = "Matrix multiplications to maximize lower dim ijk";
void matrix_multiplication16(int n,int *a, int *b,int *dest) 
{


    int i,j,k;
    int in;
    int sum;
    
    int *ain;
    int *bin;

   for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            sum=0;
            in = i*n;
            
            
            for(k=0;k<n;k+=8){
                ain =  a + in+k;
                bin = b + k*n+j;
                sum+= (*ain) * (*bin);
                sum+= *(ain+1) * (*(bin+n));
                sum+= *(ain+2) * (*(bin+2*n));
                sum+= *(ain+3) * (*(bin+3*n));
                sum+= *(ain+4) * (*(bin+4*n));
                sum+= *(ain+5) * (*(bin+5*n));
                sum+= *(ain+6) * (*(bin+6*n));
                sum+= *(ain+7) * (*(bin+7*n));
            }
            
            dest[in+j] = sum;
        }
   }


}



char matrix_multiplication16kij_descr[] = "Matrix multiplications to maximize lower dim kij";
void matrix_multiplication16kij(int dim,int *src, int *src2,int *dest) 
{
    
    int i,j,k,r;
    int kdim,idim;

    int* destin;
    int* src2in;
    
    for(i = 0; i < dim; i++){
        idim = i*dim;
        for(j = 0; j < dim; j++) {
            dest[idim+j]=0;
        }  
    }


    for(i = 0; i < dim; i++)
        for(k = 0; k < dim; k++) {
            idim = i*dim;
            r = src[idim+k];
            kdim = k*dim;
            for(j = 0; j < dim; j+= 16) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
            


            }
                
        
     }
    


}



char matrix_multiplication_descr[] = "Matrix multiplications no blocking unroll 64";
void matrix_multiplication(int dim,int *src, int *src2,int *dest) 
{


    short i,j,k,r;
    int kdim,idim;
    int* destin;
    int* src2in;
    
    for(i = 0; i < dim; i++){
        idim = i*dim;
        for(j = 0; j < dim; j++) {
            dest[idim+j]=0;
        }  
    }

    if(dim>128){
        for(i = dim-1; i >=0; i--){
            for(k = dim-1; k >=0; k--) {
                idim = i*dim;
                r = src[idim+k];
                kdim = k*dim;

                for(j = 0; j < dim; j+= 64) {
                    destin = dest+idim + j;
                    src2in = src2+kdim + j;

                    *destin += r*(*src2in);
                    *(destin+1) += r*(*(src2in+1));
                    *(destin+2) += r*(*(src2in+2));
                    *(destin+3) += r*(*(src2in+3));
                    *(destin+4) += r*(*(src2in+4));
                    *(destin+5) += r*(*(src2in+5));
                    *(destin+6) += r*(*(src2in+6));
                    *(destin+7) += r*(*(src2in+7));
                    *(destin+8) += r*(*(src2in+8));
                    *(destin+9) += r*(*(src2in+9));
                    *(destin+10) += r*(*(src2in+10));
                    *(destin+11) += r*(*(src2in+11));
                    *(destin+12) += r*(*(src2in+12));
                    *(destin+13) += r*(*(src2in+13));
                    *(destin+14) += r*(*(src2in+14));
                    *(destin+15) += r*(*(src2in+15));
                    *(destin+16) += r*(*(src2in+16));
                    *(destin+17) += r*(*(src2in+17));
                    *(destin+18) += r*(*(src2in+18));
                    *(destin+19) += r*(*(src2in+19));
                    *(destin+20) += r*(*(src2in+20));
                    *(destin+21) += r*(*(src2in+21));
                    *(destin+22) += r*(*(src2in+22));
                    *(destin+23) += r*(*(src2in+23));
                    *(destin+24) += r*(*(src2in+24));
                    *(destin+25) += r*(*(src2in+25));
                    *(destin+26) += r*(*(src2in+26));
                    *(destin+27) += r*(*(src2in+27));
                    *(destin+28) += r*(*(src2in+28));
                    *(destin+29) += r*(*(src2in+29));
                    *(destin+30) += r*(*(src2in+30));
                    *(destin+31) += r*(*(src2in+31));
                    *(destin+32) += r*(*(src2in+32));
                    *(destin+33) += r*(*(src2in+33));
                    *(destin+34) += r*(*(src2in+34));
                    *(destin+35) += r*(*(src2in+35));
                    *(destin+36) += r*(*(src2in+36));
                    *(destin+37) += r*(*(src2in+37));
                    *(destin+38) += r*(*(src2in+38));
                    *(destin+39) += r*(*(src2in+39));
                    *(destin+40) += r*(*(src2in+40));
                    *(destin+41) += r*(*(src2in+41));
                    *(destin+42) += r*(*(src2in+42));
                    *(destin+43) += r*(*(src2in+43));
                    *(destin+44) += r*(*(src2in+44));
                    *(destin+45) += r*(*(src2in+45));
                    *(destin+46) += r*(*(src2in+46));
                    *(destin+47) += r*(*(src2in+47));
                    *(destin+48) += r*(*(src2in+48));
                    *(destin+49) += r*(*(src2in+49));
                    *(destin+50) += r*(*(src2in+50));
                    *(destin+51) += r*(*(src2in+51));
                    *(destin+52) += r*(*(src2in+52));
                    *(destin+53) += r*(*(src2in+53));
                    *(destin+54) += r*(*(src2in+54));
                    *(destin+55) += r*(*(src2in+55));
                    *(destin+56) += r*(*(src2in+56));
                    *(destin+57) += r*(*(src2in+57));
                    *(destin+58) += r*(*(src2in+58));
                    *(destin+59) += r*(*(src2in+59));
                    *(destin+60) += r*(*(src2in+60));
                    *(destin+61) += r*(*(src2in+61));
                    *(destin+62) += r*(*(src2in+62));
                    *(destin+63) += r*(*(src2in+63));


                    


                }

                    
            }
        }
    }else{

        for(i = 0; i < dim; i++){
            for(k = 0; k < dim; k++) {
                idim = i*dim;
                r = src[idim+k];
                kdim = k*dim;
                for(j = 0; j < dim; j+= 32) {

                    destin = dest+idim + j;
                    src2in = src2+kdim + j;

                    *destin += r*(*src2in);
                    *(destin+1) += r*(*(src2in+1));
                    *(destin+2) += r*(*(src2in+2));
                    *(destin+3) += r*(*(src2in+3));
                    *(destin+4) += r*(*(src2in+4));
                    *(destin+5) += r*(*(src2in+5));
                    *(destin+6) += r*(*(src2in+6));
                    *(destin+7) += r*(*(src2in+7));
                    *(destin+8) += r*(*(src2in+8));
                    *(destin+9) += r*(*(src2in+9));
                    *(destin+10) += r*(*(src2in+10));
                    *(destin+11) += r*(*(src2in+11));
                    *(destin+12) += r*(*(src2in+12));
                    *(destin+13) += r*(*(src2in+13));
                    *(destin+14) += r*(*(src2in+14));
                    *(destin+15) += r*(*(src2in+15));
                    *(destin+16) += r*(*(src2in+16));
                    *(destin+17) += r*(*(src2in+17));
                    *(destin+18) += r*(*(src2in+18));
                    *(destin+19) += r*(*(src2in+19));
                    *(destin+20) += r*(*(src2in+20));
                    *(destin+21) += r*(*(src2in+21));
                    *(destin+22) += r*(*(src2in+22));
                    *(destin+23) += r*(*(src2in+23));
                    *(destin+24) += r*(*(src2in+24));
                    *(destin+25) += r*(*(src2in+25));
                    *(destin+26) += r*(*(src2in+26));
                    *(destin+27) += r*(*(src2in+27));
                    *(destin+28) += r*(*(src2in+28));
                    *(destin+29) += r*(*(src2in+29));
                    *(destin+30) += r*(*(src2in+30));
                    *(destin+31) += r*(*(src2in+31));
                


                }
            }
        }
    }
}



char verylong_src[] = "2way i, 2way j, 32 way k, zero 8 inside";
void verylong(int dim,int *src, int *src2,int *dest) 
{

    int i,j,k,r;
    int kdim,idim;

    int* destin;
    int* src2in;

    for(i = 0; i < dim; i+=2){
        idim = i*dim;
        for(k=0; k<dim; k+=8){
            destin = dest+idim+k;
            *(destin)=0;
            *(destin+1)=0;
            *(destin+2)=0;
            *(destin+3)=0;
            *(destin+4)=0;
            *(destin+5)=0;
            *(destin+6)=0;
            *(destin+7)=0;
        }
        for(k = 0; k < dim; k+=2) {
            
            r = src[idim+k];
            kdim = k*dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }

            r = src[idim+k+1];
            kdim = k*dim+dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }
                
        }
        idim = i*dim+dim;
        for(k=0; k<dim; k+=16){
            destin = dest+idim+k;
            *(destin)=0;
            *(destin+1)=0;
            *(destin+2)=0;
            *(destin+3)=0;
            *(destin+4)=0;
            *(destin+5)=0;
            *(destin+6)=0;
            *(destin+7)=0;
            *(destin+8)=0;
            *(destin+9)=0;
            *(destin+10)=0;
            *(destin+11)=0;
            *(destin+12)=0;
            *(destin+13)=0;
            *(destin+14)=0;
            *(destin+15)=0;
        }
        for(k = 0; k < dim; k+=2) {
            
            r = src[idim+k];
            kdim = k*dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }

            r = src[idim+k+1];
            kdim = k*dim+dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }
                
        }
     }
}


char verylong2_src[] = "2way i, 2way j, 32 way k, zero 2x8 outside";
void verylong2(int dim,int *src, int *src2,int *dest) 
{


    int i,j,k,r;
    int kdim,idim;

    int* destin;
    int* src2in;
    
    /*for(i = 0; i < dim; i+=2){
        idim = i*dim;
        for(j = 0; j < dim; j+=8) {
            destin = dest+idim+j;
            *(destin)=0;
            *(destin+1)=0;
            *(destin+2)=0;
            *(destin+3)=0;
            *(destin+4)=0;
            *(destin+5)=0;
            *(destin+6)=0;
            *(destin+7)=0;
        }
        idim = i*dim+dim;
        for(j = 0; j < dim; j+=8) {
            destin = dest+idim+j;
            *(destin)=0;
            *(destin+1)=0;
            *(destin+2)=0;
            *(destin+3)=0;
            *(destin+4)=0;
            *(destin+5)=0;
            *(destin+6)=0;
            *(destin+7)=0;
        } 
    }*/
    int dim2 = dim*dim;
    destin = dest;
    for(i=0;i <dim2; i+=8){
        
        *(destin)=0;
        *(destin+1)=0;
        *(destin+2)=0;
        *(destin+3)=0;
        *(destin+4)=0;
        *(destin+5)=0;
        *(destin+6)=0;
        *(destin+7)=0;
        destin+=8;
    }


    for(i = 0; i < dim; i+=2){
        idim = i*dim;
        for(k = 0; k < dim; k+=2) {
            
            r = src[idim+k];
            kdim = k*dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }

            r = src[idim+k+1];
            kdim = k*dim+dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }
                
        }
        idim = i*dim+dim;
        for(k = 0; k < dim; k+=2) {
            
            r = src[idim+k];
            kdim = k*dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }

            r = src[idim+k+1];
            kdim = k*dim+dim;
            for(j = 0; j < dim; j+= 32) {

                destin = dest+idim + j;
                src2in = src2+kdim + j;

                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
            


            }
                
        }
     }


}

char matrix_multiplication32_descr[] = "Matrix multiplications no blocking unroll 32";
void matrix_multiplication32(int dim,int *src, int *src2,int *dest) 
{


    int r;
    int kdim,idim;

    int* destin;
    int* src2in;
    int* srcin;
    int dim2 = dim*dim;
    int idimpdim;
    
    for(idim=0; idim < dim2;){
        idimpdim = idim+dim;
        destin =(dest+idim);
        for(; destin < dest+idimpdim;) {
            *(destin)=0;
            *(destin+1)=0;
            *(destin+2)=0;
            *(destin+3)=0;
            *(destin+4)=0;
            *(destin+5)=0;
            *(destin+6)=0;
            *(destin+7)=0;
            *(destin+8)=0;
            *(destin+9)=0;
            *(destin+10)=0;
            *(destin+11)=0;
            *(destin+12)=0;
            *(destin+13)=0;
            *(destin+14)=0;
            *(destin+15)=0;
            *(destin+16)=0;
            *(destin+17)=0;
            *(destin+18)=0;
            *(destin+19)=0;
            *(destin+20)=0;
            *(destin+21)=0;
            *(destin+22)=0;
            *(destin+23)=0;
            *(destin+24)=0;
            *(destin+25)=0;
            *(destin+26)=0;
            *(destin+27)=0;
            *(destin+28)=0;
            *(destin+29)=0;
            *(destin+30)=0;
            *(destin+31)=0;
            destin+=32;
        }
        srcin = src+idim;
        kdim=0;
        for(; srcin < src+idimpdim; ) {
            r = *(srcin);
            destin = dest+idim;
            src2in = src2+kdim;
            for(; destin < dest+idimpdim;) {
                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
                destin+=32;
                src2in+=32;
            }
            srcin++;
            kdim +=dim;
        }     
	    idim=idimpdim;
	 }
}


char transpose32base_descr[] = "transpose with unroll 32 with acc";
void transpose32base(int dim,int *src, int *src2temp,int *dest) {

    int i,j,k;
    int jdim;
    int sum;
    int sum2;

    int* srcin;
    int dim2 = dim*dim;
    int* src2 = malloc(4*dim2);
    int* orgsrc2 = src2;
    int* src2end = src2+dim2;
    int* destend = dest+dim2;

    for(i=0; i<dim; i+=4){
        
        
        for(jdim = 0; jdim<dim2; jdim=jdim+dim+dim)
        {
            *(src2+jdim) = *src2temp;
            *(src2+jdim+dim) = *(src2temp+1);
            src2temp+=2;
        }
        

        for(jdim = 0; jdim<dim2; jdim=jdim+dim+dim)
        {
            *(src2+1+jdim) = *src2temp;
            *(src2+1+jdim+dim) = *(src2temp+1);
            src2temp+=2;
        }

        for(jdim = 0; jdim<dim2; jdim=jdim+dim+dim)
        {
            *(src2+2+jdim) = *src2temp;
            *(src2+2+jdim+dim) = *(src2temp+1);
            src2temp+=2;
        }

        for(jdim = 0; jdim<dim2; jdim=jdim+dim+dim)
        {
            *(src2+3+jdim) = *src2temp;
            *(src2+3+jdim+dim) = *(src2temp+1);
            src2temp+=2;
        }
        src2+=4;
    }

    
   

    if(dim==32){

    //int* srcend = src+dim;
    for(j=0; j<dim;j++){
            
        src2=orgsrc2;
        for(k=0; k<dim;k++) { //j=0;j<dim;j++
            sum=0;
            sum2=0;
            srcin = src;
                
                sum += (*(srcin)) * (*(src2));
                sum2 += (*(srcin+1)) * (*(src2+1));
                sum += (*(srcin+2)) * (*(src2+2));
                sum2 += (*(srcin+3)) * (*(src2+3));
                sum += (*(srcin+4)) * (*(src2+4));
                sum2 += (*(srcin+5)) * (*(src2+5));
                sum += (*(srcin+6)) * (*(src2+6));
                sum2 += (*(srcin+7)) * (*(src2+7));
                sum += (*(srcin+8)) * (*(src2+8));
                sum2 += (*(srcin+9)) * (*(src2+9));
                sum += (*(srcin+10)) * (*(src2+10));
                sum2 += (*(srcin+11)) * (*(src2+11));
                sum += (*(srcin+12)) * (*(src2+12));
                sum2 += (*(srcin+13)) * (*(src2+13));
                sum += (*(srcin+14)) * (*(src2+14));
                sum2 += (*(srcin+15)) * (*(src2+15));
                sum += (*(srcin+16)) * (*(src2+16));
                sum2 += (*(srcin+17)) * (*(src2+17));
                sum += (*(srcin+18)) * (*(src2+18));
                sum2 += (*(srcin+19)) * (*(src2+19));
                sum += (*(srcin+20)) * (*(src2+20));
                sum2 += (*(srcin+21)) * (*(src2+21));
                sum += (*(srcin+22)) * (*(src2+22));
                sum2 += (*(srcin+23)) * (*(src2+23));
                sum += (*(srcin+24)) * (*(src2+24));
                sum2 += (*(srcin+25)) * (*(src2+25));
                sum += (*(srcin+26)) * (*(src2+26));
                sum2 += (*(srcin+27)) * (*(src2+27));
                sum += (*(srcin+28)) * (*(src2+28));
                sum2 += (*(srcin+29)) * (*(src2+29));
                sum += (*(srcin+30)) * (*(src2+30));
                sum2 += (*(srcin+31)) * (*(src2+31));

                src2+=32;
                
            
            (*dest) = sum+sum2;
            dest++;
        }

        src+=dim;

    }
    }
   
    else if(dim==64){ //standart
    
    //int* srcend = src+dim;
    for(j=0; j<dim;j++){
            
        src2=orgsrc2;
        for(k=0; k<dim;k++) { //j=0;j<dim;j++
            sum=0;
            sum2=0;
            srcin = src;
            
            
                
                sum += (*(srcin)) * (*(src2));
                sum2 += (*(srcin+1)) * (*(src2+1));
                sum += (*(srcin+2)) * (*(src2+2));
                sum2 += (*(srcin+3)) * (*(src2+3));
                sum += (*(srcin+4)) * (*(src2+4));
                sum2 += (*(srcin+5)) * (*(src2+5));
                sum += (*(srcin+6)) * (*(src2+6));
                sum2 += (*(srcin+7)) * (*(src2+7));
                sum += (*(srcin+8)) * (*(src2+8));
                sum2 += (*(srcin+9)) * (*(src2+9));
                sum += (*(srcin+10)) * (*(src2+10));
                sum2 += (*(srcin+11)) * (*(src2+11));
                sum += (*(srcin+12)) * (*(src2+12));
                sum2 += (*(srcin+13)) * (*(src2+13));
                sum += (*(srcin+14)) * (*(src2+14));
                sum2 += (*(srcin+15)) * (*(src2+15));
                sum += (*(srcin+16)) * (*(src2+16));
                sum2 += (*(srcin+17)) * (*(src2+17));
                sum += (*(srcin+18)) * (*(src2+18));
                sum2 += (*(srcin+19)) * (*(src2+19));
                sum += (*(srcin+20)) * (*(src2+20));
                sum2 += (*(srcin+21)) * (*(src2+21));
                sum += (*(srcin+22)) * (*(src2+22));
                sum2 += (*(srcin+23)) * (*(src2+23));
                sum += (*(srcin+24)) * (*(src2+24));
                sum2 += (*(srcin+25)) * (*(src2+25));
                sum += (*(srcin+26)) * (*(src2+26));
                sum2 += (*(srcin+27)) * (*(src2+27));
                sum += (*(srcin+28)) * (*(src2+28));
                sum2 += (*(srcin+29)) * (*(src2+29));
                sum += (*(srcin+30)) * (*(src2+30));
                sum2 += (*(srcin+31)) * (*(src2+31));
                sum += (*(srcin+32)) * (*(src2+32));
                sum2 += (*(srcin+33)) * (*(src2+33));
                sum += (*(srcin+34)) * (*(src2+34));
                sum2 += (*(srcin+35)) * (*(src2+35));
                sum += (*(srcin+36)) * (*(src2+36));
                sum2 += (*(srcin+37)) * (*(src2+37));
                sum += (*(srcin+38)) * (*(src2+38));
                sum2 += (*(srcin+39)) * (*(src2+39));
                sum += (*(srcin+40)) * (*(src2+40));
                sum2 += (*(srcin+41)) * (*(src2+41));
                sum += (*(srcin+42)) * (*(src2+42));
                sum2 += (*(srcin+43)) * (*(src2+43));
                sum += (*(srcin+44)) * (*(src2+44));
                sum2 += (*(srcin+45)) * (*(src2+45));
                sum += (*(srcin+46)) * (*(src2+46));
                sum2 += (*(srcin+47)) * (*(src2+47));
                sum += (*(srcin+48)) * (*(src2+48));
                sum2 += (*(srcin+49)) * (*(src2+49));
                sum += (*(srcin+50)) * (*(src2+50));
                sum2 += (*(srcin+51)) * (*(src2+51));
                sum += (*(srcin+52)) * (*(src2+52));
                sum2 += (*(srcin+53)) * (*(src2+53));
                sum += (*(srcin+54)) * (*(src2+54));
                sum2 += (*(srcin+55)) * (*(src2+55));
                sum += (*(srcin+56)) * (*(src2+56));
                sum2 += (*(srcin+57)) * (*(src2+57));
                sum += (*(srcin+58)) * (*(src2+58));
                sum2 += (*(srcin+59)) * (*(src2+59));
                sum += (*(srcin+60)) * (*(src2+60));
                sum2 += (*(srcin+61)) * (*(src2+61));
                sum2 += (*(srcin+62)) * (*(src2+62));
                sum2 += (*(srcin+63)) * (*(src2+63));
                src2+=64;
                
            
            (*dest) = sum+sum2;
            dest++;
        }

        src+=dim;

    }
    }
     else if(dim>127){
        for(j=0; j<dim;j++){
            
        src2=orgsrc2;
        for(k=0; k<dim;k++) { //j=0;j<dim;j++
            sum=0;
            sum2=0;
            srcin = src;
            
            for(i=0; i< dim; i+=64 ){   //k=0;k<dim;k++
                
                sum += (*(srcin)) * (*(src2));
                sum2 += (*(srcin+1)) * (*(src2+1));
                sum += (*(srcin+2)) * (*(src2+2));
                sum2 += (*(srcin+3)) * (*(src2+3));
                sum += (*(srcin+4)) * (*(src2+4));
                sum2 += (*(srcin+5)) * (*(src2+5));
                sum += (*(srcin+6)) * (*(src2+6));
                sum2 += (*(srcin+7)) * (*(src2+7));
                sum += (*(srcin+8)) * (*(src2+8));
                sum2 += (*(srcin+9)) * (*(src2+9));
                sum += (*(srcin+10)) * (*(src2+10));
                sum2 += (*(srcin+11)) * (*(src2+11));
                sum += (*(srcin+12)) * (*(src2+12));
                sum2 += (*(srcin+13)) * (*(src2+13));
                sum += (*(srcin+14)) * (*(src2+14));
                sum2 += (*(srcin+15)) * (*(src2+15));
                sum += (*(srcin+16)) * (*(src2+16));
                sum2 += (*(srcin+17)) * (*(src2+17));
                sum += (*(srcin+18)) * (*(src2+18));
                sum2 += (*(srcin+19)) * (*(src2+19));
                sum += (*(srcin+20)) * (*(src2+20));
                sum2 += (*(srcin+21)) * (*(src2+21));
                sum += (*(srcin+22)) * (*(src2+22));
                sum2 += (*(srcin+23)) * (*(src2+23));
                sum += (*(srcin+24)) * (*(src2+24));
                sum2 += (*(srcin+25)) * (*(src2+25));
                sum += (*(srcin+26)) * (*(src2+26));
                sum2 += (*(srcin+27)) * (*(src2+27));
                sum += (*(srcin+28)) * (*(src2+28));
                sum2 += (*(srcin+29)) * (*(src2+29));
                sum += (*(srcin+30)) * (*(src2+30));
                sum2 += (*(srcin+31)) * (*(src2+31));
                sum += (*(srcin+32)) * (*(src2+32));
                sum2 += (*(srcin+33)) * (*(src2+33));
                sum += (*(srcin+34)) * (*(src2+34));
                sum2 += (*(srcin+35)) * (*(src2+35));
                sum += (*(srcin+36)) * (*(src2+36));
                sum2 += (*(srcin+37)) * (*(src2+37));
                sum += (*(srcin+38)) * (*(src2+38));
                sum2 += (*(srcin+39)) * (*(src2+39));
                sum += (*(srcin+40)) * (*(src2+40));
                sum2 += (*(srcin+41)) * (*(src2+41));
                sum += (*(srcin+42)) * (*(src2+42));
                sum2 += (*(srcin+43)) * (*(src2+43));
                sum += (*(srcin+44)) * (*(src2+44));
                sum2 += (*(srcin+45)) * (*(src2+45));
                sum += (*(srcin+46)) * (*(src2+46));
                sum2 += (*(srcin+47)) * (*(src2+47));
                sum += (*(srcin+48)) * (*(src2+48));
                sum2 += (*(srcin+49)) * (*(src2+49));
                sum += (*(srcin+50)) * (*(src2+50));
                sum2 += (*(srcin+51)) * (*(src2+51));
                sum += (*(srcin+52)) * (*(src2+52));
                sum2 += (*(srcin+53)) * (*(src2+53));
                sum += (*(srcin+54)) * (*(src2+54));
                sum2 += (*(srcin+55)) * (*(src2+55));
                sum += (*(srcin+56)) * (*(src2+56));
                sum2 += (*(srcin+57)) * (*(src2+57));
                sum += (*(srcin+58)) * (*(src2+58));
                sum2 += (*(srcin+59)) * (*(src2+59));
                sum += (*(srcin+60)) * (*(src2+60));
                sum2 += (*(srcin+61)) * (*(src2+61));
                sum2 += (*(srcin+62)) * (*(src2+62));
                sum2 += (*(srcin+63)) * (*(src2+63));

                srcin+=64;
                src2+=64;
                
            }
            (*dest) = sum+sum2;
            dest++;
        }

        src+=dim;

    }
    }
    else{ //standart
    
    //int* srcend = src+dim;
    for(j=0; j<dim;j++){
            
        src2=orgsrc2;
        for(k=0; k<dim;k++) { //j=0;j<dim;j++
            sum=0;
            sum2=0;
            srcin = src;
            
            for(i=0; i< dim; i+=32 ){   //k=0;k<dim;k++
                
                sum += (*(srcin)) * (*(src2));
                sum2 += (*(srcin+1)) * (*(src2+1));
                sum += (*(srcin+2)) * (*(src2+2));
                sum2 += (*(srcin+3)) * (*(src2+3));
                sum += (*(srcin+4)) * (*(src2+4));
                sum2 += (*(srcin+5)) * (*(src2+5));
                sum += (*(srcin+6)) * (*(src2+6));
                sum2 += (*(srcin+7)) * (*(src2+7));
                sum += (*(srcin+8)) * (*(src2+8));
                sum2 += (*(srcin+9)) * (*(src2+9));
                sum += (*(srcin+10)) * (*(src2+10));
                sum2 += (*(srcin+11)) * (*(src2+11));
                sum += (*(srcin+12)) * (*(src2+12));
                sum2 += (*(srcin+13)) * (*(src2+13));
                sum += (*(srcin+14)) * (*(src2+14));
                sum2 += (*(srcin+15)) * (*(src2+15));
                sum += (*(srcin+16)) * (*(src2+16));
                sum2 += (*(srcin+17)) * (*(src2+17));
                sum += (*(srcin+18)) * (*(src2+18));
                sum2 += (*(srcin+19)) * (*(src2+19));
                sum += (*(srcin+20)) * (*(src2+20));
                sum2 += (*(srcin+21)) * (*(src2+21));
                sum += (*(srcin+22)) * (*(src2+22));
                sum2 += (*(srcin+23)) * (*(src2+23));
                sum += (*(srcin+24)) * (*(src2+24));
                sum2 += (*(srcin+25)) * (*(src2+25));
                sum += (*(srcin+26)) * (*(src2+26));
                sum2 += (*(srcin+27)) * (*(src2+27));
                sum += (*(srcin+28)) * (*(src2+28));
                sum2 += (*(srcin+29)) * (*(src2+29));
                sum += (*(srcin+30)) * (*(src2+30));
                sum2 += (*(srcin+31)) * (*(src2+31));
                srcin+=32;
                src2+=32;
                
            }
            (*dest) = sum+sum2;
            dest++;
        }

        src+=dim;

    }
    }
       
}



char transpose32_descr[] = "transpose with unroll 32 with acc  base impl";
void transpose32(int dim,int *src, int *src2temp,int *dest) {

    int i,j,k;
    int idim,jdim;
    int sum;
    int* src2in;
    int* srcin;
    int dim2 = dim*dim;
    

    int* src2 = malloc(4*dim2);


    for(i=0; i<dim; i++)
        for(j=0; j<dim; j++)
        {
            src2[j*dim+i] = src2temp[i*dim+j];
        }


    for(i = 0; i < dim; i++){
        idim=i*dim;
        for(j = 0; j < dim; j++) {
            sum=0;
            jdim=j*dim;
            for(k = 0; k < dim; k+=32){
                srcin = src+idim+k;
                src2in = src2+jdim+k;
                
                sum += (*(srcin)) * (*(src2in));
                sum += (*(srcin+1)) * (*(src2in+1));
                sum += (*(srcin+2)) * (*(src2in+2));
                sum += (*(srcin+3)) * (*(src2in+3));
                sum += (*(srcin+4)) * (*(src2in+4));
                sum += (*(srcin+5)) * (*(src2in+5));
                sum += (*(srcin+6)) * (*(src2in+6));
                sum += (*(srcin+7)) * (*(src2in+7));
                sum += (*(srcin+8)) * (*(src2in+8));
                sum += (*(srcin+9)) * (*(src2in+9));
                sum += (*(srcin+10)) * (*(src2in+10));
                sum += (*(srcin+11)) * (*(src2in+11));
                sum += (*(srcin+12)) * (*(src2in+12));
                sum += (*(srcin+13)) * (*(src2in+13));
                sum += (*(srcin+14)) * (*(src2in+14));
                sum += (*(srcin+15)) * (*(src2in+15));
                sum += (*(srcin+16)) * (*(src2in+16));
                sum += (*(srcin+17)) * (*(src2in+17));
                sum += (*(srcin+18)) * (*(src2in+18));
                sum += (*(srcin+19)) * (*(src2in+19));
                sum += (*(srcin+20)) * (*(src2in+20));
                sum += (*(srcin+21)) * (*(src2in+21));
                sum += (*(srcin+22)) * (*(src2in+22));
                sum += (*(srcin+23)) * (*(src2in+23));
                sum += (*(srcin+24)) * (*(src2in+24));
                sum += (*(srcin+25)) * (*(src2in+25));
                sum += (*(srcin+26)) * (*(src2in+26));
                sum += (*(srcin+27)) * (*(src2in+27));
                sum += (*(srcin+28)) * (*(src2in+28));
                sum += (*(srcin+29)) * (*(src2in+29));
                sum += (*(srcin+30)) * (*(src2in+30));
                sum += (*(srcin+31)) * (*(src2in+31));
                
            }
            dest[idim+j]=sum;
        }
    }
    
}


char transpose32noacc_descr[] = "transpose with unroll 32 without acc";
void transpose32noacc(int dim,int *src, int *src2,int *dest) {

    int r;
    int idim;
    
    int* destin;
    int* src2in;
    int* transin;
    int dim2 = dim*dim;
    
    int *srcin;

    int* trans = malloc(4*dim2);
    int *orgtrans = trans;

    idim=0;
    for(; idim<dim2;){
        
        srcin = src+idim;
        transin = trans++;
        for(; srcin<src+idim+dim; )
        {
            

            *(transin) = (*(srcin));
            *(transin+dim) = (*(srcin+1));
            srcin+=2;
            transin+=(2*dim);
            

        }
        destin = dest + idim;
        for(;destin<dest+idim+dim;){
            *(destin)=0;
            *(destin+1)=0;
            *(destin+2)=0;
            *(destin+3)=0;
            *(destin+4)=0;
            *(destin+5)=0;
            *(destin+6)=0;
            *(destin+7)=0;
            *(destin+8)=0;
            *(destin+9)=0;
            *(destin+10)=0;
            *(destin+11)=0;
            *(destin+12)=0;
            *(destin+13)=0;
            *(destin+14)=0;
            *(destin+15)=0;
            *(destin+16)=0;
            *(destin+17)=0;
            *(destin+18)=0;
            *(destin+19)=0;
            *(destin+20)=0;
            *(destin+21)=0;
            *(destin+22)=0;
            *(destin+23)=0;
            *(destin+24)=0;
            *(destin+25)=0;
            *(destin+26)=0;
            *(destin+27)=0;
            *(destin+28)=0;
            *(destin+29)=0;
            *(destin+30)=0;
            *(destin+31)=0;
            destin+=32;
        }
        idim+=dim;
    }



    transin= orgtrans;
    for(; transin < orgtrans+dim2; ){
        idim=0;

        destin = dest;
        for(; idim < dim2;) {
            
            r = (*(transin));
            src2in = src2;
            
            for(; destin < dest+idim+dim;){
                
                *destin += r*(*src2in);
                *(destin+1) += r*(*(src2in+1));
                *(destin+2) += r*(*(src2in+2));
                *(destin+3) += r*(*(src2in+3));
                *(destin+4) += r*(*(src2in+4));
                *(destin+5) += r*(*(src2in+5));
                *(destin+6) += r*(*(src2in+6));
                *(destin+7) += r*(*(src2in+7));
                *(destin+8) += r*(*(src2in+8));
                *(destin+9) += r*(*(src2in+9));
                *(destin+10) += r*(*(src2in+10));
                *(destin+11) += r*(*(src2in+11));
                *(destin+12) += r*(*(src2in+12));
                *(destin+13) += r*(*(src2in+13));
                *(destin+14) += r*(*(src2in+14));
                *(destin+15) += r*(*(src2in+15));
                *(destin+16) += r*(*(src2in+16));
                *(destin+17) += r*(*(src2in+17));
                *(destin+18) += r*(*(src2in+18));
                *(destin+19) += r*(*(src2in+19));
                *(destin+20) += r*(*(src2in+20));
                *(destin+21) += r*(*(src2in+21));
                *(destin+22) += r*(*(src2in+22));
                *(destin+23) += r*(*(src2in+23));
                *(destin+24) += r*(*(src2in+24));
                *(destin+25) += r*(*(src2in+25));
                *(destin+26) += r*(*(src2in+26));
                *(destin+27) += r*(*(src2in+27));
                *(destin+28) += r*(*(src2in+28));
                *(destin+29) += r*(*(src2in+29));
                *(destin+30) += r*(*(src2in+30));
                *(destin+31) += r*(*(src2in+31));
                destin+=32;
                src2in+=32;
                
            }
            transin++;
            idim+=dim;
            
        }
        src2+=dim;

    }

    
}





/*********************************************************************
 * register_matrix_multiplication_functions - Register all of your different versions
 *     of the matrix multiplication  with the driver by calling the
 *     add_matrix_multiplication_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_matrix_multiplication_functions() {
    
    
    /* ... Register additional test functions here */

add_matrix_multiplication_function(&transpose32base ,transpose32base_descr );  
//add_matrix_multiplication_function(&transpose32 ,transpose32_descr );  
//add_matrix_multiplication_function(&matrix_multiplication32, matrix_multiplication32_descr);   





//add_matrix_multiplication_function(&transpose32noacc ,transpose32noacc_descr );  
//add_matrix_multiplication_function(&matrix_multiplication, matrix_multiplication_descr);   
//add_matrix_multiplication_function(&verylong, verylong_src);   
//add_matrix_multiplication_function(&verylong2, verylong2_src);  

//add_matrix_multiplication_function(&matrix_multiplication32inc, matrix_multiplication32inc_descr);   
    //add_matrix_multiplication_function(&matrix_multiplication_blocking, matrix_multiplication_block_descr);   

    //add_matrix_multiplication_function(&unroll16, unroll16_descr);   
    //add_matrix_multiplication_function(&unroll32, unroll32_descr);  
    //add_matrix_multiplication_function(&blockreuse, blockreuse_descr);  



//add_matrix_multiplication_function(&matrix_multiplication16, matrix_multiplication16_descr);   
//add_matrix_multiplication_function(&matrix_multiplication16kij, matrix_multiplication16kij_descr); 




}

















