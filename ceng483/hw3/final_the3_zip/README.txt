Hello,

If you want to run for test queries;

put nn.py, dset.py,  test_gray/ and test.txt in the same directory. Run:

$ python nn.py

The script will, as it is, train the network for 30 epoch, and create:

logs.txt -- log file
logs.p -- dictionary of parameters
estimations_test.npy -- Test estimations
lossplot.png -- loss plot
accplot.png -- acc plot

If you want to run for validation set, do the exact same thing but write 

'acc_val_loader' instead of 'acc_test_loader' in line 282.

If you want to do anything else, god help you.

Take Care.
