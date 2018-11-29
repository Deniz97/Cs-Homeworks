# Prevent Octave from thinking that this
# is a function file:

1;

%%%%% Helper Functions

function retval = minion_pdf(q,a)
    retval = q*a/exp(q+a);
endfunction

function [w_pred,s_pred, Y_pred] = generate_w_s ()
    %never exdeeds 1/(e*e) which is around 0.135
    a = 0;
    b = 10; %very close to zerwo when either w or s exceeds 20
    c = 0.14;
    do
        w_pred = a+(b-a)*rand;
        s_pred = a+(b-a)*rand;
        Y_pred = rand*c;
    until (Y_pred <= minion_pdf(w_pred,s_pred))
    
endfunction 

function retval = generate_poisson (lambda)
    U = rand;
    i = 0;
    F = exp(-lambda);
    while(U >= F);
        F=F + exp(-lambda) * lambda^i/gamma(i+1);
        i = i+1;
    end;
    retval = i;
endfunction

function retval = generate_exp(lambda)
    retval = -(1/lambda) * log(rand);
endfunction

function retval = std_normal_pdf(x)
    retval = exp(-(x^2)/2)/sqrt(2*pi);
endfunction

function x_pred = generate_std_normal()
    % we employ the rejection method
    a = -5;
    b = 5; %practically close to zero when outside [-10,10]
    c = 0.4; %never exdeeds 0.5
    do
        x_pred = a+(b-a)*rand;
        Y_pred = rand*c;
    until (Y_pred <= std_normal_pdf(x_pred))
endfunction


%%%%%% END HELPER FUNCTIONS



%%%% QUESTON 1
function p = question1 (experiment_count)
    N = experiment_count; %number of experiments
    success_count = 0; %number of times an iteration has success (ie. >6 constraint)
    
    while N>0;
        
        n = generate_poisson(20); %number of minions we caught this iteration
        satisfaction_count = 0; %number of times the constraint is satisfied
        while n>0;
            [w,s] = generate_w_s;
            if w>=2*s;
                satisfaction_count += 1;
            endif;
            if satisfaction_count > 6;
                success_count += 1;
                break;
            endif;
            n = n-1;
        end;
        N = N -1;
    end;
    p = success_count/experiment_count;
endfunction

%question1(390)
%%%%

%%%% QUESTION 2
function mean = question2(experiment_count)
    N = experiment_count; %number of experiments
    total_weight = 0; %total weight of all experiments
    
    while N>0;
        
        n = generate_poisson(20); %number of minions we caught this iteration
        curr_total_weight = 0; %total weight in this experiment
        while n>0;
            [w,s] = generate_w_s();
            curr_total_weight += w;
            n-=1;
        end;
        total_weight += curr_total_weight;
        N = N -1;
    end;
    mean = total_weight/experiment_count;
endfunction

%mean = question2(3900)
%%%%

%%% QUESTION 3

function mean = question3(experiment_count) 
    N = experiment_count;
    total_sum = 0; %sum of desired values
    
    while N>0
        A = generate_exp(2);
        B = generate_std_normal();
        total_sum += (A+2*B)/(1+abs(B));
        N = N - 1;
    end
    
    mean = total_sum / experiment_count;
endfunction

%%%





question1(3900)
question2(3900)
question3(3900)
