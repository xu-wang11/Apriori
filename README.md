Apriori
=======

implement Apriori algorithm 
##问题描述#
- 本程序实现了Apriori算法，采用位来表示每一个状态，在这种情况下，A是B的子集,就意味着A & B = A.
- 在从第K代生成第K+1代时，当两个元素进行join操作生成一个含有K+1个元素的孩子时，比如（1,2）, (2, 3), (1, 3)每两个都会生成相同的结果，为了保证结果的正确，我们在对AB进行join的时候要要求A包含最小的元素且不包含最大的元素， B包含最大的元素且不包含最小的元素。

- 本实验数据集为北大邓志鸿老师的实验数据。

##时间测试#
对mushroom.dat进行时间测试，当支持度为0.25时用时为1.2S,当支持度为0.2时用时为5s.
