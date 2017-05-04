deal with signal in one thread

1. 功能简介
  它的主要功能就是通过采样的方式，给程序中cpu的使用情况进行“画像”，通过它所输出的结果，我们可以对程序中各个函数（得到函数之间的调用关系）耗时情况一目了然。在对程序做性能优化的时候，这个是很重要的，先把最耗时的若干个操作优化好，程序的整体性能提升应该十分明显，这也是做性能优化的一个最为基本的原则—先优化最耗时的。
  {
	1. cpu-profiler
	2. heap-checker
	3. heap-profiler
  }
2. 安装
1) 64位操作系统先安装libunwind(ubuntu) 
  sudo apt-get install libunwind-dev 
  sudo apt-get install graphviz // 图形工具
源码路径:https://github.com/gperftools/gperftools
安装步骤)
tar -zxvf gperftools-2.5.tar.gz
cd gperftools-2.5
./configure
make
sudo make install
/sbin/ldconfig

3. 使用
本例子在于多线程程序运行过程中通过信号来动态产生性能的消耗图,可以直观的得出系统的性能瓶颈。PS:在后台服务程序中信号推荐在一个线程中执行，防止出现不可预知的错误

// TODO pprof --dot signal_example sig.profile >> sig.dot

// dot -Tpng sig.dot>>sig.png



