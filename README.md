上海地铁线路查询
-----

开发板：乐鑫ESP32-S3 Lilygo AMOLED
框架：Arduino
数据来源：https://service.shmetro.com/czxx/index.htm
算法：Dijkstra
作者：Jianliang Shen

## 下载方法
VScode+PlatformIO

## 操作

* 功能1：查看线路，双击选择起点，再次双击选择终点。
* 功能2：搜索站点，按首拼音缩写，匹配，双击进入站点选择，完成后显示结果。
* 按键说明：
  * 右键单击：右翻页/输入
  * 右键双击：确定/下一级
  * 右键长按：向右/下滑动
  * 左键单击：左翻页/删除
  * 左键双击：返回上一级,
  * 左键长按：向上/左滑动,

## 效果图
![](/pics/ui.jpg)
![](/pics/lines.jpg)
![](/pics/start.jpg)
![](/pics/end.jpg)
![](/pics/result.jpg)