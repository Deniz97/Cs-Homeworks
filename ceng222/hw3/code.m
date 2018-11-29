function retval = minion_pdf (w,s)
    retval = w*s/exp(w+s);
endfunction

function [w_pred,s_pred] = generate_w_s ()
    %never exdeeds 1/e which is around 0.4
    a = 0;
    b = 30; %very close to zero when either w or s exceeds 30
    c = 1;
    do
        w_pred = a+(b-a)*rand;
        s_pred = a+(b-a)*rand;
        Y_pred = rand*c;
    until (Y_pred > minion_pdf(w_pred,s_pred))
    
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

%%%% QUESTON 1
function p = prob_over_six (experiment_count)
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

% prob = prob_over_six(39000)

%%%%

%%%% QUESTION 2
function mean = mean_total_weight(experiment_count)
    N = experiment_count; %number of experiments
    total_weight = 0; %total weight of all experiments
    
    while N>0;
        
        n = generate_poisson(20); %number of minions we caught this iteration
        curr_total_weight = 0; %total weight in this experiment
        while n>0;
            [w,s] = generate_w_s;
            curr_total_weight += w;
            n-=1;
        end;
        total_weight += curr_total_weight;
        N = N -1;
    end;
    mean = total_weight/experiment_count;
endfunction

% my_mean = mean_total_weight(39000)

%%%%

%%% QUESTIN 3

function retval = simulate_exp(lambda)
    retval = -1/lambda * log(rand);
endfunction

function retval = std_normal_pdf(x)
    retval = exp(-(x^2)/2)/sqrt(2*pi);
endfunction

function x_pred = simulate_std_normal()
    % we employ the rejection method
    a = -10;
    b = 10; %practically close to zero when outside [-10,10]
    c = 1; %never exdeeds 0.5
    do
        x_pred = a+(b-a)*rand;
        Y_pred = rand*c;
    until (Y_pred > std_normal_pdf(x_pred))
endfunction

function mean = run_q3(experiment_count) 
    N = experiment_count;
    total_sum = 0; %sum of desired values
    
    while N>0
        A = simulate_exp(2);
        B = simulate_std_normal();
        total_sum += (A+2*B)/(1+abs(B));
        N = N - 1;
    end
    
    mean = total_sum / experiment_count;
endfunction

% m = run_q3(39000)

%%%























