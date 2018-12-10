%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% In this tutorial, we are going to implement dimension reduction technique
% called Principal Component Analysis (PCA) on the simple toy                                            %
% dataset which is generated in section(I)).                              %
%                                                                         %
% References:                                                             %
%    - textbooks: "Pattern Classification" -                              %
%                 R.O.Duda, P.E. Hart and D.G. Stork                      %
%   - textbooks: "Pattern Recognition and Machine Learning" -             %
%                 Christopher M. Bishop,                                  %
%                                                                         %                                    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;close all; clc;

%% Section I: forming and plotting the dataset
mu = [2,5]; sigma = [1,1.5;1.5,3];
C1X = (mvnrnd(mu,sigma,100))';
mu = [4,1];sigma = [1,1.5;1.5,3];
C2X = (mvnrnd(mu,sigma,100))';
% mean computation
X = [C1X,C2X];
m1 = mean(C1X')';                % mean of the first  class
m2 = mean(C2X')';                % mean of the second class

subplot(2,2,1);
plot(C1X(1,:),C1X(2,:),'+'); hold on; grid on;plot(C2X(1,:),C2X(2,:),'ko');
plot(m1(1,1),m1(2,1),'*', 'color','r'); hold on; grid on;
plot(m2(1,1),m2(2,1),'*', 'color','r'); ylim([-10 10]);xlim([-10 10]);
title('Dataset');

%% Dimension Reduction using linear projection and pca
% Section II: let see what happen when we decrease dimension from 2D to 1D
% without any technique 

w = (m2-m1);                     % computing the weight  
y = w'*X;                        % linear projection
subplot(2,2,2);x_axis  = zeros(1,100);
plot(y(1:100),x_axis,'+', 'color','blue'); grid on; ylim([-1 1]);xlim([-125 100]); hold on;
plot(y(101:200),x_axis,'ko', 'color','black'); grid on; ylim([-1 1]);xlim([-125 100]);
title('Linear projection');

%% Ok, the result is bad as the plot show. Now, lets reduce to 1D from 2D
% using Principal Component Analysis (PCA)
% you can not your matlab pca (e.g. y = pca(X)) or similar functions. :)
% you can use other matlab functions such as invariance or covariance.
% you can use loop, and please plot your results  
% your code should goes on here....'

X2 = X - mean(X)
cov = (1/(size(X2,1) - 1)) * X2' * X2; %'
[y, _] = eigs(cov, 1);
        
subplot(2,2,3);
plot(y(1:100),x_axis,'+', 'color','blue'); grid on;  hold on;
plot(y(101:200),x_axis,'ko', 'color','black'); grid on; 
title('My PCA');

%%
%Section III: Comparing your results with matlab pca function
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% if you want to see what should your results be please uncomment the
%%% following section and run the code. 
y = pca(X);
figure; x_axis  = zeros(1,100);
subplot(2,2,4);
plot(y(1:100),x_axis,'+', 'color','blue'); grid on;  hold on;
plot(y(101:200),x_axis,'ko', 'color','black'); grid on; 
title('Matlab PCA');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
