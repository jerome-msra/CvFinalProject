%mex resizeArray
arr=[11:19;21:29;31:39;41:49;51:59;61:69];
selRows=[1 3];
selCols=[2:4 5 9];
[rarr,rdims]=ResizeArray(arr,selRows,selCols);