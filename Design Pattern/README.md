# 设计模式

## 设计模式是什么

- 设计模式是一套被反复使用、多数人知晓的、经过分类的、代码设计经验的总结

> 就是想出套路去干某件事

```
1+2+3+...+n ==> (1+n)*n/2
```

## 设计模式的目的

- 为了代码可重用性、让代码更容易被他人理解、保证代码的可靠性
- 使代码编写真正工程化，是软件工程的基石脉络，如同大厦的结构一样

## 模式是什么

- 模式是指从生产经验和生活经验中经过抽象和升华提炼出来的核心知识体系
- 模式其实就是解决某一类问题的方法论

## 创建形

> 研究高效的创建对象

- 单例模式
- 抽象工厂模式
- 建造者模式
- 工厂模式
- 原型模式

## 结构型模式

> 设计对象的结构和关系

- 适配器模式
- 桥接模式
- 装饰模式
- 组合模式
- 外观模式
- 享元模式
- 代理模式

## 行为型模式

> 设计对象的行为

模板方法模式，命令模式，迭代器模式，观察者模式，中介者模式，备忘录模式，解释器模式，状态模式，策略模式，职责链模式，访问者模式

## 原则

- 减少耦合，增强复用性，降低代码的开发维护扩展成本
  > 耦合关系是指某两个事物之间如果存在一种相互作用、相互影响的关系，那么这种关系就称"耦合关系"
  
  > 复杂度：高，代码质量不高，可维护性差，复用性差，不易扩展。
  
  > 耦合度：无 不可能 ，低 合理，过高不容易维护。但复用性和扩展性。

## 开发流程
- 优先降低复杂度，尽量降低耦合度  
  1. 利用单一职责原则，开闭原则，里氏代换原则降低复杂度。
  2. 通过迪米特法则减少耦合度
  3. 通过依赖倒置原则消除可以没有的耦合


## 单一职责原则（single Responsibility principle）
- 一个方法只做一件事情

```javascript
// function View(url, data, dom, flag){
//     if(localStore.getItem('list') && !flag){
//         var arr = JSON.parse(localStore.getItem('list'));
//         var htmlStr = '';
//         arr.forEach(function(ele, index){
//             htmlStr += '<li>' + ele.name + '</li>';
//         });
//         dom.innerHtml = htmlStr; 
//     }
//     $.ajax({
//         url: url,
//         data: data,
//         success: function(json){
//             var arr = JSON.parse(json);
//             localStore.setItem = ('list', json); 
//             var htmlStr = '';
//             arr.forEach(function(ele, index){
//                 htmlStr += '<li>' + ele.name + '</li>';
//             });
//             dom.innerHTML = htmlStr; 
//         }
//     })
// }
// View('xxx', 'page=1', ul);
// 
// 
//  按单一原则拆分：
function GetData(callBackArr){
    this.getData = function (url, param){
        $.agax({
            url: url,
            data: param,
            success: function(json){
                callBackArr.forEach(function(ele, index){
                    ele.do(json);
                })
            }
        })
    }
}
function Render(dom){
    this.dom = dom;
    this.do = function(){
        var htmlStr = '';
        arr.forEach(function(ele, index){
            htmlStr += '<li>' + ele.name + '</li>';
        });
        this.dom.innerHTML = htmlStr;
    }
}
var oR = new Render(ul);
// 缓存数据
function CacheData(type){
    this.do = function(type){
        localStorage.setItem(type, data)
    }
    this.returnCacheData = function(){
        return localStorage.getItem(type);
    }
}
var OC = new CacheData('list');
var oG = new GetData([oR, oC]);
if(oC.returnCacheData()){
    if(navigator.onLine){
        oR.do(oC.returnCacheData());
    }else{
        oG.getData()
    }
}else{
   oG.getData();
}
```

## 开闭原则

- 一个软件实体如类、模块和函数应该对外扩展开放，对修改关闭
- 面向扩展开放，面向修改关闭jquery extend,同时增强代码复用性

## 里氏代换原则 L Subsituation Principle

- 任何基类可以出现的地方，子类一定可以出现。通俗的来讲就是：子类可以扩展父类的功能，但不能改变父类原有的功能。
- 一个父类可以访问的接口，父类忙着其他事情，子类可以去访问。

```javascript
function Rectangle(){
    this.height;
    this.width;
    this.setHeight = function(height){
        console.log('setHeight')
        this.height = height;
    }
    this.setWidth = function(width){
        this.width = width;
    }
    this.getHeight = function(){
        return this.height;
    }
    this.getWidth = function(){
        return this.width;
    }
}
Square.prototype = new Rectangle();
function Square(){
    this.setHeight = function(height){
        this.height = height;
        this.width = width;
    }
    this.setWidth = function(width){
        this.setHeight(width);
    }
}
var oS = new Rectangle();
oS.setWidth(200);
oS.setHeight(200);
function Resize(o){
    while(o.getHeight() < o.getWidth()){
        o.setHeight(o.getWidth() + 1);
    }
    console.log('over');
}
Resize(oS);

var oG = new Rectangle();
oG.setWidth(200);
oG.setHeight(200);
// Resize(oG); //死循环
```