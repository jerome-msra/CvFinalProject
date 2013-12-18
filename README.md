CSE 548 Computer Vision Final Project
==============
This project is the final project of CSE 548 Computer Vision in Stony Brook University.

Author
----
* Junwei Jason Zhang
* Jian Jiang
* Zhenxiao Guo

Goal
---
Establish accurate one-to-one mapping between two faces using method combining 3D geometry information and 2D texture information.

Specifically, in the aspect of 2D image matching, we use non-rigid registration. In the paper of *Efficient MRF Model for Non-rigid Image Matching*, a non-rigid deformation method based on MRF is introduced and use TRW-S to minimize the MRF energy function. We follow this paper to finish the 2D image matching.

Algorithm
---
* Discrete Ricci Flow, which has been already finished with Prof. David Gu
* Markov Random Field
* ICM
* TRW-S to minimize MRF energy function