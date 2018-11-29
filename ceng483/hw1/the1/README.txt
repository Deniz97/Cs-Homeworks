Hi.

Here is the usage.

Your interface into the script is the method called give_best_results(s_type,q_type,k).

To use the script, first open the python3 interpreter.

Then import the script using:

>> from vision import *

Then call the following method with the arguments you want:

>> give_best_results(s_type="dense_sift",q_type="val",k=-1)

s_type: either "sift" or "dense_sift", use dense_sift or omit if you want to use whatever we originally used.
q_type: either "val" or "test", obvious.
k: The cluster count for k_means. Either give it by hand or give -1 or omit for default value.

So you will probably either use

>> give_best_results(q_type="val") or give_best_results(q_type="test")

After running the script, which may take time, you will find many pickle files in your directory which you can ignore, and a file in the following format:

>val_dense_result_256.txt

or

>val_result_128.txt

or

>test_dense_result_64.txt

Where the "dense_" is appented to beggining for dense sift, the number at the end is the K value, end either "val_" or "test_" is appended to beggining.

Bye.