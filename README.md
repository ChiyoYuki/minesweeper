# 一个命令行扫雷游戏  
## v2.0.0版本更新：  
~~是的我就是跳号带师~~  
1.添加了linux适配  
: 采用了  
: ```
#ifdef __linux__  
//linux代码  
#else  
//windows代码    
#endif  ```  
: 不知道为什么不能使用`#ifdef __WIN32`  
2.为每个数字添加了不同的颜色  
3.调整了行间距  
4.使用键盘控制光标移动代替输入坐标  
5.改变了胜负判断的逻辑  
## v1.0.1版本更新：<br>
1.修改了一处提示文本<br>
## v1.0.0版本内容：<br>
1.用户输入三个参数：地图的长、宽以及地雷的数目<br>
2.生成地图并打印在屏幕上<br>
3.用户通过输入格子的横纵坐标来打开格子<br>
4.未点开的格子为白色问号；点开的数字格子为绿色数字；点开的空白格子为空格；点开的地雷为红色“X”<br>
5.最大支持生成30*30的地图<br>
## 现有最新版本不足之处<br>
~~1.输入坐标的方式不够直接~~<br>
2.缺乏计时模块<br>
3.每次进入程序只能进行一次游戏<br>
4.第一次点击可能是有雷的格子<br>
## 下一版本目标<br>
~~1.实现键盘控制光标打开格子以代替输入坐标~~    **已完成**<br>
2.实现再来一局功能<br>
