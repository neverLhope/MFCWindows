windows程序设计大作业
  功能实现
    1.应用停靠显示数据
    2.右键可以进行添加，修改，删除等操作
    3.在停靠中修改数据可以更新到视图中
    4.停靠和视图之间通过自定义Message来传消息
    5.在document中存储了两个标志变量
    6.可以进行文件存储和打开
  修改：
    1.停靠中修改选项颜色可以更新到视图中
    2.图表数据和图表操作封装到了同一个类中。回来之后我又仔细考虑了一下，我将数据放到app中和直接放在图像基类CGraphic中是一样的。之前的想法有很大的问题，封装用的很不好。