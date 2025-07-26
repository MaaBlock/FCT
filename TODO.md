[branch]
```mermaid
graph TD
    1[去除beginFrameTicker]
    2[转换wnd的enableAutoReviewport为组件]
    2-->1
    3[为Wnd添加组件功能,
    将上层功能变为添加到wnd的组件，
    从而实现上层解耦，
    从而防止wnd层调用上层代码]
    3-->2
```
requeire:
使用entt
```mermaid
graph TD
    1[添加使用entt的窗口EventHandler]
```
[main]
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