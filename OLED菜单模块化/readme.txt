这里状态机的思路是先定义好各个状态下根据外界或内部输入进行改变的状态跳转函数,
然后在主函数里根据状态不同执行不同的任务,在每个周期里都先获取外界或内部输入
后执行一次状态跳转函数,再执行状态对应任务