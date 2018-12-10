%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% In this tutorial, we are going to implement the least square for        %
% classification and compute the sum of squared errors on the simple toy  %
% dataset which is generated in section(I)).                              %
%                                                                         %
% References:                                                             %
%    [1] textbooks: "Pattern Classification" -                            %
%                 R.O.Duda, P.E. Hart and D.G. Stork                      %
%    [2] textbooks: "Pattern Recognition and Machine Learning" -          %
%                 Christopher M. Bishop, section 4.1.3.                   %
%                                                                         %
%                                     %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;close all; clc;
%% Section I: forming and plotting the dataset

mu = [-7,-1]; sigma = [1,1.5;1.5,3];
C1X = (mvnrnd(mu,sigma,100))';
C1Y = ones(100,1);
mu = [4,1];sigma = [1,1.5;1.5,3];
C2X = (mvnrnd(mu,sigma,100))';
C2Y = -ones(100,1);
plot(C1X(1,:),C1X(2,:),'+'); hold on;
plot(C2X(1,:),C2X(2,:),'ko');
ylim([-10 10])
xlim([-10 10])

%%%
X = [C1X,C2X]';                % X is the dataset
x0 = ones(200,1);              % x0 is dummy input 
X = [X,x0];                    % adding dummy input (x0) to the dataset
T = [C1Y;C2Y];                 % T is the true target values 


%% Section II: Your implementation will be in this section...
% You have to implement the vectorized version. 
% This is simple, you should just follow section 4.1.3 of Ref [1]
% you can not use the matlab functions such as lsqlin. :)
% the result should be plotted.
% your implementation should go here ...

W = transpose(T)*transpose(pinv(X))
x=-10:.01:10;
y=(W(1)*x+W(3))/W(2);
plot(x,y)

sse=sum((W*transpose(X)-transpose(T)).^2)


















%% Section III: Comparing your results
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% if you want to see what should your results be please uncomment the
%%% following section and run the code. 

% wMatlab = lsqlin(X, T);
% yMatlab = -wMatlab(3)/wMatlab(2) - (wMatlab(1)/wMatlab(2))*X;
% plot(X, yMatlab,'linewidth',2,'color','black');hold on; grid on;




