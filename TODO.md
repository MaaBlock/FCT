# [branch]
## 添加Window模块
1.添加Window命名空间 
  在Window命名空间下添加归属于Window的模块<div/>
2.Window内部添加一个类型Map，
能根据类型获取对应的模块对象，
如
```c++
AutoViewport av = wnd->getModule<AutoViewport>
```
3.实现添加模块
如
```c++
wnd->addModule<AutoViewport>();
```
4.移除Context中的beginFrameTicker
## 添加事件处理
```mermaid
graph TD
    1[添加使用entt的窗口EventHandler]
```
## 统一new和delete
将不小心使用的new 和 delete 都改为使用FCT_NEW FCT_NEWS FCT_DELETE FCT_DELETES
# [main]
```mermaid
graph TD
    1[简化命名，使得其符合直觉]
    2[对于用来自定义的函数，添加_前缀,
    表明当使用这些函数的时候,
    用户需要知道自己在干什么]
    1-->2
```
```mermaid
graph TD
    2[改名create为build]
    1[拆分某些build的逻辑]
    3[固定某些build的逻辑]
    2-->1-->3
```
a.g. PipelineResource

```mermaid
graph TD
    1[将Pipeline系列分离为俩个类，
    一个负责平台，
    一个负责生成默认资源]
```