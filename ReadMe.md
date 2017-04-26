# 常用数据结构与算法的实现

## KMP字符串匹配算法

有时候我们需要在一大段字符串中得到找到我们想要的位置，这个时候KMP字符串匹配算法是一种比较好的选择。

首先我们需要进行**匹配字符串的预处理**，即我们要在一个字符串中找另外一个字符串，我们需要预处理这个字符串。主要是查看这个字符串上有没有“最长公共子序列”。最长公共子序列是是KMP算法的核心概念。这决定了我们一位位向前移动匹配的时候，如果遇到匹配失败的我们应该如何处理，是整个匹配字符串向前挪动一位吗，其实不是挪动一位，只要我们可以知道最长公共子序列，那么我们就可以直接在比较发现不匹配之后，移动一个更大的距离，而不是一格，继续比较。而我们所说的那个“更大的距离”，就是由“最长公共子序列”决定的，我们需要知道，在已经匹配到的子字符串两头最大的公共部分是多少，下次比较的时候我们直接在匹配失败的时候把最大公共部分的前面那部分平移过来，前面那一部分最长公共子序列的下一位开始比较。

预处理还是很简单的：

```c++
//我们首先先进行预处理，需要delete这个堆区数组
    int *pre_handle_arr = pre_handle(patch_string);
    
    
    //然后进行比较
    int compare_continue = -1;
    
    int patch_string_index = 0;
    int goal_string_index = 0;
    
    //退出这个循环主要是两种情况，首先就是目标字符串走完了，还有就是要匹配别人的小字符串走完了，前者代表失败，后者代表成功
    while(patch_string_index < patch_string.length() && goal_string_index < goal_string.length()){
        
        if(patch_string[patch_string_index] == goal_string[goal_string_index]){
            compare_continue = pre_handle_arr[patch_string_index];
            patch_string_index++;
            goal_string_index++;
        }else{
            //如果没有匹配成功，并且这个时候compare_continue是-1，说明在已匹配子串中没有最大公共子序列
            //那么我们直接匹配目标字符串的下一位
            if(compare_continue == -1){
                goal_string_index++;
                patch_string_index = 0;
            }else{
                //如果在某一位匹配失败，并且有公共子序列，那么就利用公共子序列，将公共子序列的前半部分向前挪到后半部分的位置
                patch_string_index = compare_continue + 1;
                
                compare_continue = pre_handle_arr[compare_continue];
//                cout << patch_string_index << "," << compare_continue << endl;
            }
        }
        
//        cout << patch_string_index << "," << goal_string_index << endl;
    }
```

道理很简单，除了第一位，每一位的字符都要和tmp+1这个位置的字符比对一下。如果相等，那么就可以说明最大公共子字符串又扩充了一位。

在逻辑上比较繁琐的就是进行字符串比较的那个过程，有点绕：

```c++
//我们首先先进行预处理，需要delete这个堆区数组
    int *pre_handle_arr = pre_handle(patch_string);
    
    
    //然后进行比较
    int compare_continue = -1;
    
    int patch_string_index = 0;
    int goal_string_index = 0;
    
    //退出这个循环主要是两种情况，首先就是目标字符串走完了，还有就是要匹配别人的小字符串走完了，前者代表失败，后者代表成功
    while(patch_string_index < patch_string.length() && goal_string_index < goal_string.length()){
        
        if(patch_string[patch_string_index] == goal_string[goal_string_index]){
            compare_continue = pre_handle_arr[patch_string_index];
            patch_string_index++;
            goal_string_index++;
        }else{
            //如果没有匹配成功，并且这个时候compare_continue是-1，说明在已匹配子串中没有最大公共子序列
            //那么我们直接匹配目标字符串的下一位
            if(compare_continue == -1){
                goal_string_index++;
                patch_string_index = 1;
            }else{
                //如果在某一位匹配失败，并且有公共子序列，那么就利用公共子序列，将公共子序列的前半部分向前挪到后半部分的位置
                patch_string_index = compare_continue + 1;
                
                compare_continue = pre_handle_arr[compare_continue];
                //cout << patch_string_index << "," << compare_continue << endl;
            }
        }
        
//        cout << patch_string_index << "," << goal_string_index << endl;
    }

```

首先我们要注意循环的条件，必须两个string都没有遍历完才可以进行循环，两个之中有其中一个遍历完了就不可以循环了。

我们主要使用patch_string_index和goal_string_index两个索引分别遍历匹配小字符串和目标字符串。如果相等，当然是这两个索引都会自增，然后比较目标字符串和匹配小字符串的下一位。如果发现不匹配了，首先就要看看以匹配的子串里面有没有最大公共子字符串（使用compare_continue==-1）。如果没有，那么直接使用匹配字符串的第0位去匹配，目标字符串的下一位就好了（patch_string_index=0赋值，goal_string_index自增）。如果发现有最大公共子字符串那就让最大公共子字符串的后一位去匹配目标字符串的当前位置。所以对于比较的结果，一共是三类情况。



## 环状队列

因为队列只能从尾部加入，从顶部移出，所以我们使用传统数组的方式会有问题，因为随着头部内容的不断移出以及尾部的不断移进，整个队列会逐渐往线性表的后部靠拢，这样子在线性表的前半部分就会有很大的空间浪费。如果要把已经贴近后半部分的内容挪到靠近线性表头部的位置，这就需要大量的开销，所以我们就需要换装队列。

环状队列本质上还是线性表，通过取模的操作获得环状的效果。

环状队列比较什么时候满的时候我们，除了可以维护一个存储了环状队列当前容量的变量之外还可以预留一个空位置。为了统一我们的逻辑，我们必须设定一套在所有的时期都适用的判定环状队列空或者满的办法。我们设定头指针与尾指针重合代表空，尾索引取模如果比头索引取模之后小1，或者比头索引大maxsize-1那么就说明队列已经满了。rear永远指向没有值的下一个要插入的位置，头索引永远指向下一个要推出的值，除非队列是空的。

这次实现中使用了模板类，因为模板类不是类，所以模板类是不能拆的，应该放在一个头文件中，要不就会报错。此外我们就是要注意取模和边界条件。这样子就可以了。总体的实现还是比较简单的。

## 走迷宫算法

走迷宫算法是一个对栈结构的非常不错的利用，我们我们通过一个栈来获得我们已经走过的路径，如果栈顶的节点在所有方向上都走不通，那就进行弹栈操作。在倒数第二个节点上进行各个方向的尝试。任何曾经进过栈的节点都会被记录下来，防止走重复的路。

这里在编程里面碰到了一些问题，比如在C++11中，我们发现枚举和结构体实例化的时候我们不再需要在前面再加struct和enum这两个关键词。直接当做一个类使用就好了。

此外我们发现int a\[\]\[\]，实际上a变量这个时候并不是一个二维指针，而是一个数组对象，所以说我们没有办法把他当做一个二维指针使用。其实使用栈空间来申请二维数组，获取其二维指针的方式并不是没有，但是比较困难，并且语法比较容易混淆，所以我们使用new的方式产生线性数组，以及指针数组来产生二维数组。

在if和while条件上我也出现了不止一次的错误，注意非（！）与或等运算符组合起来的关系。

还要注意的是，枚举是一种常量，不能进行自增操作。

## 中缀表达式转后缀表达式

这也是一个使用栈的经典案例，我们使用栈来保存符号，而变量字符会被直接输出。符号一共有6种，加、减、左右小括号，乘除。而这个“符号栈”的入栈和出栈规则如下：

- 符号是有优先级的，正常情况下，符号会一位一位进入栈中，如果碰到了一个运算符，不比栈顶运算符的优先级小，那么这个运算符就要正常入栈。
- 出栈的策略非常简单，如果整个表达式走完了就把所有的符号弹出并且输出，如果表达式没有走完，但是有一个比栈顶运算符优先级小的运算符要入栈，那就先要将栈中的所有元素推出。
- 括号的处理也很重要，一般情况下，左括号我们直接入栈就好，遇到右括号，那么我们就需要我们将右括号与左括号之间的弹栈就好。左括号了右括号不会出现在后缀表达式中。




## 环装链表

环装链表。环装链表主要就是链表的最后一个元素的next指针会指向链表的头部。

首先是数据成员的设计，在实践过程中发现，环装链表最好不要使用first指针，使用last指针才是比较正确的。因为使用first指针的时候如果我们需要在链表的头部增加节点，那么最后一个节点的next指针要指向新的头部。那这就涉及到一个问题，我们怎么自能让最后一个节点的指针指向新的头部，如果我们只有first指针，那么我们只能遍历整个链表，然后去修改最后一个节点的next指针，这样子开销很大。

所以在环形链表中应该使用last指针，last指针指向链表的最后一个节点，这样子无论从链表的头部开始尾部添加元素都会变得比较简单。

另外我们发现在模板中，我们不能为形参设定缺省值。另外加在头部和尾部的节点也要在逻辑上单独处理。

在删除节点的过程中，我们对于最后一个节点的删除要尤其注意，因为删除最后一个节点之后，我们要重新定位last，所以我们需要单独处理，需要单独记录一下倒数第二个节点的指针，以便让last指针定位。

最后在说一下析构函数，析构函数就是不断执行链表第一个元素的删除操作就好了。



## 双向链表

当我们需要向头尾两个方向遍历的时候我们就需要双向链表了，为了体现双向链表的优势，我们打算实现goleft、goright、addleft、addright、deleteleft、deleteright，这几个函数，主要的工作就是让一个指针不断在链表中移动，可以理解为是双向链表这个对象和迭代器的结合体。

其实在实现链表的时候书上一直都建议使用空头部节点的设计，这种方式有很多的好处，可以统一逻辑，减少边界条件的判断。在双向链表的实现中我们也使用这种被推荐的设计。此外我们依旧要实现一个换装双向链表。

这里唯一要注意的问题就是这个空白的头结点的左右指针怎么指，为了保证在遍历链表的过程中，让左边最边上一个元素的在往左边走就是空白头结点，而空白头结点再往左边走是右边第一个节点，这样子循环起来。我们需要精心设计空白头结点的通往左节点的指针和右节点的指针。

有关于双向链表的初始化问题比较有一起，比较精妙的设计是初始化一个空白的头结点，然后让这个空白头结点的左右节点指针全部指向自己，这样子做的好处就是可以统一所有的关于插入和删除节点的逻辑。并且上文所说的头结点左右指针的“精心设计”也可以和一般节点的逻辑统一起来。

意外因为头结点比较重要最好不要删除，所以我们在删除的时候会弹出警告。

这样子双向链表就完成了。

## 树

### 二叉树

树是一种非常重要的数据结构，二叉树更是重中之重。我们可以知道。使用数组来表示一个二叉树是一个非常容易的事情。我们从数组的1号位置开始记录，我们在1号位置存储的是树的根。对于一个深度为k的数组来说，我们最多可以容纳2^k-1个元素。

我们使用数组对二叉树进行了实现，对于i号元素来说，他的左节点就在i\*2处，右节点在i\*2+1处。我们知道在此基础之上注意数组溢出的问题就可以了。

子树的删除使用的是递归程序，在删除子树的根节点之后我们知道再去删除子树的左右节点就可以了。

二叉树的数组实现对于完全二叉树来说是一种比较简单合适的解法，但是如果是不太完全的二叉树，那么就会出现空间的浪费，所以使用二叉树的链表表示更为合适。

此外我们还进行了树的链表表示，链表表示的难点就是析构的部分，我觉得使用一种合理的遍历方式就可以进行析构。

### 树的广度优先搜索

树的链表形式在析构的时候需要广度优先搜索，广度优先搜索的最需要的就是队列这样一个结构，我们首先将根节点放在队列中，我们析构在队列头部的节点，如果这个节点有子女，那么子女也会全部加入在队列尾部。通过不断析构头部元素，当队列为空的时候就代表整个树的析构就完成的。



### 二叉树的遍历

二叉树有三种常见的遍历方式，分别是前序遍历、中序遍历、后序遍历。具体的遍历方式和这个名字是一样的。遍历的过程是一种递归算法，三种遍历方式区别就是每一次递归子树根节点扫描的次序。如果是前序遍历那扫描的顺序就是“打印根->递归左子树->递归右子树”；如果是中序遍历，那扫描的顺序就是“递归左子树->打印根节点->递归右子树”；如果是后序遍历，那么扫描的顺序就是“递归左子树->递归右子树->打印根节点”。这样子就完成了扫描。

因为我们的二叉树一共提出了两种实现，一种是链表方式，一种是数组方式。所以我们打算为这两种实现的类设定一个基类。这个基类也是一个模板类，所有函数和操作和我们的两种实现一样，我们利用多态，以及虚函数，来保证他们的基类就是前序遍历、中序遍历、后序遍历的形参。

这里稍微提一下C++语法的事情。首先基类的析构函数必须是虚函数。我们知道派生类的构造函数会默认调用基类的缺省构造函数，派生类的析构函数也会调用基类的析构函数。这种特性注定了我们基类的析构函数首先必须是虚函数，并且不能是纯虚函数，因为派生类的析构会用上。

但是我们发现使用外部函数传入Tree类型形参的方式没法很好地进行递归操作。因为一个是链表一个是数组，逻辑没有办法统一。

所以我们使用成员函数的方式对Tree进行遍历。使用两套不一样的逻辑。这里我们对数组二叉树的遍历进行实现。

### 二叉树的非递归遍历

二叉树而非递归遍历可以节省更多内存占用，我们可以通过使用一个栈来进行前、中、后序遍历。

先说一下非递归的前序遍历，我们的主要思路就是不断将子树的根节点放入栈中，并打印根节点。然后让遍历的指针往左子树不停走。也就是根节点在入栈的时候就要打印，然后当已经没有左节点可以再走的时候，我们就可以进行弹栈操作了，弹栈之后就去看右子树。

然后是非递归的中序遍历，我们还是先不断让根节点入栈，然后不断向左节点移动。中序遍历是在弹栈的时候进行打印。弹栈之后看右子树。

后序遍历是最麻烦的非递归遍历方式。主要就是子树的根会最早进栈，并且在子树的根的右子树还没有遍历的时候，不会出栈，出栈打印。

面对栈的状态我们可以很清楚地知道，前序遍历和中序遍历的栈中右子树节点对应的父节点是不会出现在栈中的，二者的区别主要是栈中元素的打印时间不一样，一个是在入栈，一个是在出栈。后序遍历栈中元素会多一些，因为根节点和右子树的根节点全部都会出现在栈中。

我们在链表二叉树中进行了非递归遍历的实现。

首先是后序遍历，这个遍历的我们需要有“几个注意”，因为是非递归的，所以我们需要对整个的遍历顺序过程极为了解，我们整体遍历的趋势应该是首先“一口气向左子树走到底”，在这过程中，所有的根节点一直入栈，直到“左不下去”了然后弹栈，弹栈的时候要看看栈中的节点有没有有没有右子树，如果有右子树，要优先进入右子树的遍历，也是在右子树中“一口气左到底”，然后不断入栈。在非递归的后序遍历算法中，入栈和出栈都是一种正反馈的过程，只要入栈就会一口气让一串左子树入栈，只要出栈，除非碰到栈顶元素有右子树（右子树会入栈，然后因为正反馈，会让右子树的所有左子树全部入栈），要不弹栈就不会停。

在这个算法的实现中我们需要两个额外空间，一个是栈，一个是标记栈中节点的右子树有没有被遍历的数组。

```c++
template<class T>
void LinkedBTree<T>::post_order() {
    //我们进行后序遍历，首先创建一个栈空间。
    //栈空间存放树的节点
    now = root;
    LinkedBItem<T> **stack = new LinkedBItem<T> *[100];
    //索引从-1开始，指向当前的栈顶
    int stackIndex = -1;
    //我们建立一个数组，主要是为了查看栈中节点的有没有右子树需要遍历，如果已经被遍历了，那就可以安心弹栈，如果没有被遍历
    //那就只能只能再把右节点压栈。压栈是一个"正反馈"的过程，一旦出现了压栈，那就会一压到底，不断向左节点走，直到不能再压
    //一旦压到不能再压，那就会进入弹栈程序，弹栈主要做的就是检查当前节点的右子树。
    int *hasScanRight = new int[100];

    //初始化数组
    for (int i = 0; i < 100; ++i) {
        hasScanRight[i] = 0;
    }


    //首先我们先让根节点入栈，然后触发"入栈正反馈"，直到now是空指针为止
    stack[++stackIndex] = root;

    if (root->right != 0) {
        hasScanRight[stackIndex] = 1;
    }

    while (stackIndex != -1) {
        now = stack[stackIndex];

        while (now->left != 0) {
            stack[++stackIndex] = now->left;
            //入栈之后查看右节点的情况，然后修改那个查看右子树是不是已经被遍历的数组
            if (stack[stackIndex]->right != 0) {
                hasScanRight[stackIndex] = 1;
            }

            now = now->left;
        }

        //当完成"入栈正反馈"之后，我们就可以弹栈过程，弹栈的时候我们就可以看看是不是右子树有没有东西
        while (stackIndex != -1 && hasScanRight[stackIndex] == 0) {
            //如果右子树没有东西，那就进入正常的弹栈过程，弹栈也是一个正反馈过程如果，如果一直右子树没有东西，就可以一直弹
            cout << stack[stackIndex]->element << " , ";
            stackIndex--;
        }

        //从这个while中出来有两种情况，一种就是发现右子树还在的，一种就是stack已经空了
        if (hasScanRight[stackIndex] == 1) {
            //如果右子树有东西，那么我们就要进行新一轮的压栈操作，压栈的之后还要看看新入栈的节点有没有右子树
            stack[stackIndex + 1] = stack[stackIndex]->right;

            //右节点已经入栈，修改hasScanRight数组
            hasScanRight[stackIndex] = 0;
            stackIndex++;

            if (stack[stackIndex]->right != NULL) {
                hasScanRight[stackIndex] = 1;
            }
        }
    }

    cout << endl;
    //析构申请的资源
    delete[]stack;
    
    delete[]hasScanRight;
}
```

然后我们实现前序遍历和中序遍历，这两种遍历方式的实现基本是一样的，除了栈中元素打印的时间不一样。前序遍历的主要工作就是在子树根节点入栈的时候打印树节点内容。当已经没有左子树根节点可以入栈的时候，我们进行出栈过程，出栈过程也是一个正反馈的过程，只有当当前节点有右子树的时候才会停止，但是当前节点也会被弹出。此时，新发现的右子树会入栈并打印自身，然后又是一系列的“正反馈入栈”。整个过程讲以stack全部弹出并且没有新的节点加入画上一个句号。

```c++
template<class T>
void LinkedBTree<T>::pre_order() {
    //前序遍历也需要一个树节点指针的栈区
    LinkedBItem<T> **stack = new LinkedBItem<T> *[100];
    //栈索引从-1开始
    int stackIndex = -1;
    now = root;
    //然后我们让根节点进入栈
    stack[++stackIndex] = root;
    cout << stack[stackIndex]->element << " , ";
    //然后开始前序遍历，栈不为空，遍历就继续
    while (stackIndex != -1) {
        //如果栈顶元素有左子树，激活入栈正反馈
        now = stack[stackIndex];
        //如果栈顶元素没有左子树了那就不用再压栈了
        while (now->left != 0) {
            stack[++stackIndex] = now->left;
            cout << stack[stackIndex]->element << " , ";
            now = now->left;
        }

        //到这里，栈顶元素就是没有左子树的二叉树节点了，我们弹栈，并且查看右子树，如果要弹栈的元素有右子树，那么在弹栈之后把右子树加入
        //弹栈也是一个正反馈的过程，直到弹空或者发现当前栈顶节点有右子树（此时当前节点也会被弹出）
        while (stackIndex != -1) {
            //如果发现当前节点有右子树，那就停止弹栈，但是当前节点也会弹出
            if (stack[stackIndex]->right != 0) {
                //进行最后一次弹栈
                stackIndex--;
                //然后将右子树加入栈中
                stack[stackIndex + 1] = stack[stackIndex + 1]->right;
                stackIndex++;
                //入栈要打印
                cout << stack[stackIndex]->element << " , ";
                //结束循环，回到外层循环顶部进行正反馈入栈，入栈会激活新的入栈
                break;
            } else {
                //当前节点没有右子树直接弹栈，并且如果一直没有右子树，那就一直弹，也是正反馈
                stackIndex--;
            }
        }
    }
    cout << endl;

    //空间回收
    delete[]stack;
}
```

中序遍历和前序遍历的代码基本上一致，就是打印节点的时机不一样。

```c++
template<class T>
void LinkedBTree<T>::in_order() {
    //创造一个栈
    LinkedBItem<T> **stack = new LinkedBItem<T> *[100];
    //栈顶索引
    int stackIndex = -1;

    //根节点入栈
    stack[++stackIndex] = root;

    while (stackIndex != -1) {
        now = stack[stackIndex];

        //触发入栈正反馈
        while (now->left != 0) {
            stack[++stackIndex] = now->left;
            now = now->left;
        }

        //现在栈顶节点已经没有左子树了
        //我们可以出栈了
        while (stackIndex != -1) {
            //只要没有右子树出现，那就一直执行出栈操作
            //出现右子树，弹出当前节点，加入右子树根节点
            if (stack[stackIndex]->right != 0) {
                //打印当前节点
                cout << stack[stackIndex]->element << " , ";
                //将当前节点换成右子树根节点
                stack[stackIndex] = stack[stackIndex]->right;
                //退出循环，并且进入外层循环的左子树入栈过程
                break;
            } else {
                //没有右子树，那就一直弹栈
                cout << stack[stackIndex]->element << " , ";
                stackIndex--;
            }
        }
    }
    cout << endl;
    delete[]stack;
}
```









# 常用算法整理与总结

这一部分我们主要介绍一些我们无暇实现但是依旧是耳熟能详的算法。我们会尽可能加入一些思路甚至伪代码的实现。这一部分的内容主要来自于我看《算法导论》的体会与总结。

## 插入排序

插入排序的思路就像我们按顺序整理一套扑克牌一样。我们以从小到大排序为例，我们从第一位开始将一个牌从当前位置抽出，然后让这张牌与之前的牌作比较。比这张牌大的牌都依次往前移一位，直到之前的牌比抽出的牌小。这样子就会空出来一个位置，将抽出的牌放到这个位置就好了。插入排序的特点就是我们抽出的牌的前面的牌都是已经排好序的。我们要做的实际上就是不断让一个新的值插入到一个已经排好序的序列中。

伪代码：

```
//插入排序，我们假设为从小到大排序
//形参是输入和数组的长度
insert_sort(A[],len)
	for i <- 0 to len
		do 
		//首先我们获取当前位置的元素
		tmp <- A[i]
		//这里激活一个嵌套循环，让获取的元素和之前的元素做比较
		for j <- i to 0
			do
			if A[j] >= tmp
				then
				A[j+1] = A[j]
			else
				A[j] = tmp
				break;
```

这个是一个时间复杂度为n^2的算法。

## 选择排序

选择排序是一种看起来更笨拙的排序方式，时间复杂度也是n^2。他的总体原理是一开始遍历整个数组，将最小的放在数组的第一个位置。然后遍历数组的剩下部分，将最小的放在数组的第二个位置，直到最后所有的元素都各得其所。

## 合并（归并）排序

### 合并排序算法思路

这是一种比较快的排序算法，时间复杂度达到了nlogn。他的思路就是将整个要排序的集合不断拆分，然后再两两合并，在合并的过程中进行排序操作。归并排序是一个递归算法，要合并的两个子列都是已经经过合并排好序的。所以这个算法的核心就是对已经排好序的两个数组进行合并，合并之后依旧是排好序的数组

数组合并伪代码：

```
//输入为两个数组和两个数组的大小，从小到大的排序
merge(A[],B[],m,n){
	i <- 0
	j <- 0
	q <- 0
	result[m+n]
	while i < m && j < n
		do
		if A[i] > B[j]
			then
			result[q] = B[j]
			j++
			q++
		else
			result[q] = A[i]
			i++
			q++
	//两个数组中有其中一个数组还会剩余元素，我们将其拷到要返回的目标数组中
	for i1 <- i to m
		do
		result[q] = A[i1]
		q++
	
	for j1 <- j to n
		do
		result[q] = A[j1]
		q++
}
```

以上就是归并排序的核心部分，但是实际上外部还需要一个函数来进行驱动

```
//归并排序，形参为要排序的乱序数组
merge_sort(A[],len){
	//将数组进行拆分
	mid = len/2
	A1[mid]
	A2[len-mid-1]
	for i <- 0 to mid
		do
		A1[i] = A[i]
	for j <- 0 to len-mid-1
		do 
		A2[j] = A[mid+1+j]
	merge_sort(A1[] , mid)
	merge_sort(A2[] , len-mid-1)
	A[] = merge(A1[] , A2[] , mid , len-mid-1)
}
```

### 改造归并排序求逆序对个数

这个是一个到腾讯的笔试中出的一个考题，可以通过修改归并排序来获得一个数组中逆序对的个数。我们的主要的思路如下，依旧是一个递归的思路，但是我们需要在递归的过程中加入一个计数的步骤。

假设A[]数组，前后分为A1[m]和A2[n]两个部分。A1中的元素我们在逻辑上不需要特殊处理，然后A2中的元素我们在进行合并的时候要特殊处理。比如，A2中的第x个元素合并完之后就在A中的y位置。这个时候我们就知道这个元素对应的逆序就是，m-(y-x)。y-x算出的是A1中比这个元素小的元素，而m-(y-x)就是A1中比这个元素大的元素，所以这样子就可以算出与这个元素相关的逆序数。通过不断的遍历和向上递归，整个数组的逆序数就算出来了。

## 冒泡排序

这是一种乍一看和插入排序很像的排序方式，但是实际上有着本质上的不同。我们以从小到大排列为例，我们首先要注意冒泡的方向。将从小到大排列中我们可以从右边开始，将小的元素向左冒泡，也可以从左边开始将打的元素向右冒泡。每一轮冒泡都可以讲当前子列最大或者最小值挪到数组的两端。

```
//冒泡即是将打的值从左侧
bubble_sort(A[] , len)
	//冒泡的轮数
	for i <- 0 to len
		do
		//每一轮要冒泡的元素
		for j <- 0 to len - i -1
			do
			if(A[j]>A[j+1])
				tmp = A[j+1]
				A[j+1] = A[j]
				A[j] = tmp
```



## 霍纳规则的多项式运算

这个就是秦九昭算法，将多项式的计算变成了一个每一步都逻辑相同的递归。对于多项式来说我们不断提出前n项共有的X来进行化简。直到最后在每一个都可以进行ax+b的递归。



## 堆排序

堆排序是一种精妙的设计。堆是一种完全二叉树，他除了最后一层的每一层都是满的，最后一层也优先放满树的左边。这样子就可以造成一个非常好的效果就是，如果我们使用二叉树的数组表示来表示这个堆，那么这个数组的有内容的前半部分是完全满的，对于已经占用的空间来说，完全没有任何空间浪费。堆有一个很不错的性质就是在表达堆的数组中，假设一共占用了n个位置，那么n/2+1开始都是这个堆的叶子节点。

最大堆与最小堆是我们用来分别进行从大到小与从小到大排序的工具。以最大堆为例，一个节点的值永远比他的两个儿子节点要打，堆的根节点以及堆中所有子树的根节点的值都是在他那个子树里最大的。这里就涉及一个堆结构的保持问题，如果我们在一个子树的根部换上一个比儿子节点小的值，那么我们就需要进行堆的递归重构。重构的过程就是让这个子树的根节点和他的两个儿子相比较（这两个儿子都是所在的子树都是一个最大堆），如果根节点不是这两个儿子中最大的，那么就和这两个儿子中值比较大的那个儿子交换。然后继续递归那个值发生交换的子树最大堆。直到已经没有值可以交换为止，这样子堆就完成了重构，并保持了原有的性质。

对于一个杂乱无章的数组来说，堆排序分为两个部分，一个是堆的构造，一个是堆排序。堆是一个自下而上构造的过程，我们从数组的中间位置开始向前进行子堆重构，直到整个堆的所有内容都进行了，整个堆形成了最大堆，这个时候根节点就是最大值，我们将根节点和数组中的最后一个有效值进行交换，再让数组剩下的部分再进行一次堆重构。然后不断把数组剩下的部分进行整个堆的重构，这样子最后就可以得到一个排好序的数组。下面是伪代码。

```
//这里是子堆重构的函数
//输入参数第一个是堆的数组表示，n是要重构的子堆的根节点。而这个根节点的两个儿子都是各自最大堆的根节点
childRebuild(A[],n)
	//我们首先要看的就是A[]与左右子节点的比较，选出一个最大值和子树的根做交换
	//之后的这几个if就是在比较三个值之间的最大值
	//首先和左节点做比较
	if A[n] > A[n*2]
		then
		large <- n
	else
		large <- n*2
	
	if A[large] < A[n*2 +1]
		then
		large <- n*2 +1
	
	//选完之后我们就可以进行交换操作了，如果不需要交换，重构结束
	if large != n
		then
		tmp <- A[large]
		A[large] <- A[n]
		A[n] <- tmp
		//继续在子堆上递归
		childRebuild(A[],large)
```

使用这个函数也可以进行堆合并的操作。主要的操作就是使用一个叶子节点来放在两个堆的根上。然后执行一次从跟开始的堆重构工作。

我们通过这个根节点的两个儿子都是各自最大堆的根节点的特殊子堆的重构函数，我们通过自下而上的推构造方式进行无序数组的堆构造。

```
//输入是无序数组和这个数组的长度，我们要把这个数组的内容构造成堆
heap_build(A[] , len)
	//我们堆的最低一层非叶子节点开始往回遍历数组，重构
	for j <- len/2 downto 1
		do
		childRebuild(A[] , j)
```

这样子我们就完成了堆的构造工作。下面我们就可以进行堆排序了。为了节省空间，我们就把排好序的部分放在这个堆数组中，也就是放在堆数组的最后一个。通过让每一次从堆中选出的最大值和整个数组的最后一个值交换就好，然后我们对堆的剩下部分不断进行重构，最后就可以得到一个排好序的序列了

```
//利用之前两个函数，进行堆排序核心算法
//输入为要排序的数组和数组的长度len，数组的第一位是空白的，我们这个len是数组不空白的部分
heap_sort(A[] , len)
	
	//乱序的时候进行大规模重构
	heap_build(A[],len)
	
	//每一次我们选出来一个值，所以重构的过程需要反复len-1次
	for j <- 1 to len-1
		do
		//让最大值和数组最后一位交换(节省空间)，然后重构
		//交换
		tmp <- A[1]
		A[1] <- A[len - 1]
		A[len-1] <- tmp
		//我们将堆的有效长度-1，让下次只重构剩下的部分
		len--;
		//因为左右子树都是最小堆，所以只要进行根节点的重构就好
		childRebuild(A[],1)	
//我们就这样通过最大堆来构成了一个从小到大排列的序列
```

其实我们也可以修改交换的位置来用最小堆实现这个过程。



## 最大优先队列

这是一种与与堆排序有着异曲同工的。我们知道在堆排序中，节点在堆中只有可能下降，这个过程叫做堆下降。在最大（最小）优先队列中，算法的核心在于“堆上升”。在最大优先队列中，在堆中的一个元素的优先级只有可能突然上升，这个元素就有可能出现堆上升的操作。

此外我们还可以基于堆上升的操作完整最大优先队列的插入操作。只要就是将一个元素插入在堆数组的尾部，并且对这个元素执行堆上升操作。从而维持堆的性质。

而在堆的根部的元素就是优先级最高的。我们有时候需要取出最大值。最大值取出之后我们还需要进行堆的重构，重构的过程和堆排序很像，我们把数组最后的值放到根节点处，然后进行重构。重构就是使用之前的递归“堆下降”工作。



现在我们实现一下最大优先队列。使用伪代码。

```
//导出最大优先队列的最优先元素，也就是A[1]，然后我们就要使用重构堆，重构的方法就是把数组最后一个节点放在根节点处，然后重构。这个是最大优先队列功能的核心。导出的永远都是优先级最高的节点。
//导出优先级最高的节点
extra_max(A[],len)
	tmp = A[1]
	print tmp
	A[1] = A[len]
	childRebuild(A[],1)
```

节点上升函数，可以应对某一个节点优先级增大的情况。并且是在堆中加入节点的重要部分。

```
//实现节点上升的函数
//三个形参，第一个是堆的数组表现，我们对A的要求就是A已经要是一个符合最大堆规范的对，第二个要修改的这个堆中的节点在数组中的位置，第三个是要将这个节点修改成的值，这个值只能变大不能变小，这个是最大优先队列的一个原则。
increasing_key(A[],i,key)
	//首先看看输入值是不是合法，对应堆节点的值是不是变大了
	if(A[i] > key)
		then
		//输入值没有变大，输入违法
		return;
	
	A[i] <- key
	//然后我们进行递归的堆上升操作，让新改变的节点向上浮
	while i > 1 && A[parent(i)] < A[i]
		do
        //我们执行交换操作
        tmp <- A[i]
        A[i] <- A[parent(i)]
        A[parent(i)] <- tmp
        i <- parent(i)
```

然后就是节点添加的函数，我们将节点放在最后，然后对这个节点进行堆上升操作。

```
insert_item(A[],newEle)
	A[++len] <- newEle
	increasing_key(A[],len,newEle)
```

我们可以使用堆的插入操作来进行堆的构建，实际上我认为对于堆的插入操作，我们唯一可以做的就是把一个一个新的值放在堆数组的最后一位，然后采用“堆上升”操作对堆进行重构。

除了二叉堆，我们还有D叉堆，这种堆结构在每个节点都有更多的节点，但是堆的高度会变小。这种变化，会对“堆下降”操作带来负担，但是堆上升操作会快很多。



我们这里总结一下堆，我们发现我们的重构过程容易搞混。这里我们要先说说从根部开始的重构，我们在之前叙述的时候，我们常说“堆上升，堆下降”。堆上升是我觉得是一种“调整”，堆下降是一种“重构”。比如堆下降过程，他保证的是下降节点的左右子树也同样是堆，这个过程是在乱序数组推构建（自下而上的堆下降重构）、以及堆排序的时候叶节点换到跟节点的重构工作；而堆上升是在堆插入和堆中某一个节点的优先级变大，也会进行节点的堆上升工作。



## 快速排序

快速排序是一种最佳的排序算法。虽然最坏运行情况很差 ，但是平均排序性能很好。并且因为使用的是就近的空间，所以并不需要额外的空间。相比之下，虽然归并排序也有不错的性能表现，但是因为归并排序需要额外的空间需要，所以快速排序是一种更好地选择。

快速排序的特点就是想起来很简单，但是实现起来就有不同的效果。他的核心在于“桩”这个概念，在每一个子列处理完之后，我们要达到一个效果，（假设是从小到大排列），我们要做的就是让比桩大的值都放在桩的右边，比桩小的值都放在桩的左边。然后将桩左边和右边的值分别递归，进行子列的处理。直到子列的大小只有1，递归停止。因为桩一般情况下都在两头，最后桩的位置又非常重要，我们要在最后将在数列中部符合要求的值和在头尾的桩进行交换，而什么叫“符合要求”我们要根据“桩”在头部开始尾部，以及这个队列最终是要从小到大还是从大到小排列有关。

整个算法的设计如下。除了指向我们需要快排的子列的首指针和尾指针，我们还需要两个指针，一个指针指向我们正在扫描的数组元素（初始化的时候指向0位置），还有一个指针（如果是从小到大排列）大值与小值的边界（**一开始放在子列（前边界索引-1）的位置**）。

```c++
template<class T>
void part_quick_sort(T *inputArr, int start, int end);

template<class T>
void quick_sort(T *inputArr, int len) {
    //这个是一个递归的算法
    part_quick_sort(inputArr, 0, len - 1);
}

//这个部分是要递归的函数，
template<class T>
void part_quick_sort(T *inputArr, int start, int end) {
    //判定递归停止
    if (start >= end ) {
        //递归停止
        return;
    }

    //我们需要初始化两个指针，一个指针从头开始扫描
    int i = start - 1;
    //这个变量是桩，桩在数组的最后
    int pile = inputArr[end];
    int tmp = 0;
    for (int j = start; j <= end; ++j) {
        //j这个索引从子列的头部开始扫描，如果发现桩比数组小，那么就让j当前指向的元素和i+1所在的元素交换，并且i向前移动
        //对于i这个索引来说，我们要保证i是比桩小的，i+1是比桩大的。
        //我们要把比桩小的往前扔
        if (inputArr[j] <= pile) {
            tmp = inputArr[j];
            inputArr[j] = inputArr[i + 1];
            inputArr[i + 1] = tmp;
            i++;
        }
    }
    //等循环结束之后，i所在的位置就是桩经过换到中间之后的位置。现在我们拆分数组，进行递归
    part_quick_sort(inputArr, 0, i - 1);
    part_quick_sort(inputArr, i + 1, end);
}
```

因为快速排序拥有比较好的平均性能，所以我们必须为快速排序加入一些随机化的因素来体现其平均性能的优势。所以我们的“桩”（在算法导论中叫做“主元元素”）是随机选取的，我么通过摇一个随机数在要处理的子列中选出一个随机的元素和尾部的元素做一次交换，然后再用尾部的元素做桩，以此达到了加入随机因素的结果。

## 非比较排序

我们之前用的全部都是基于比较的排序，现在我们可以看到一些不基于比较的排序。对于基于比较的排序，我们可以使用树状图的方式来判定这种排序的时间复杂度。非比较排序就不适合这种方式了。

总得来说非比较排序的时间复杂度甚至还要更小。

### 计数排序

计数排序是一种用空间换时间的典型案例。计数排序的主要思路就是我们将一个数列中比每一个数小或者相等的数的数目记录下来。比如说，在我们需要排列的数组中有一个数是5，然后在这个数组中我们发现比5小的数有3个，那么我们就要记录：“比5小的数有3个”，体现在编程中，就是我们在一个临时数组的第5个位置记录一个数字”3“。然后我们最后直接在输出数组的第4个位置填一个5就可以了，因为5比三个数字大嘛。

然后这又有新的问题，那就是如果有很多个相同的数字怎么办。比如我们发现”5“一共有多个，那么我们会在向输出数组添加一个5的时候，在计数的临时数组中我们就要把5对应的值-1。

我们怎么输出？在整理完临时的计数数组的时候，我们要依照输入数组的内容查询临时数组，并且将查到的内容进行输出数组的构建，直到输入数组被完全遍历。

总之，计数排序我们一共涉及3个数组，输入、输出、临时计数。下面我们进行C++语言的实现。

这里先提及一个实现问题，就是指针的引用问题，为了保证我们的指针的指向在函数之内可以进行真正意义上的改变。指针的引用要注意“*”与“&”的顺序：

```
func(int *&p)
```

在编程中我们还遇到一个问题，就是栈区数组变量与指针变量实际上是不一样的。我们要注意区分。如果是要传数组的引用，那就是：

```
func(int &p[数组大小])
```

我们可以看到指针是指针，数组变量是数组变量，虽然他们有一定的一致性，并且数组变量还可以赋给指针。使得新的指针就是一个指向栈区的指针。但是数组变量是不可以改变的。数组变量不可以改变用其他数组变量来赋值，也不可以进行引用传参。根据网上的说法，数组变量并不是真正意义上的变量，所以在内存上实际上没有这个数组变量的空间，在程序运行的时候作为立即数存在，也就没有修改和引用的说法。

所以说数据变量的存在和指针之间很容易产生混淆和误解，对于数组，我们尽可能使用new+指针指向的方式来声明。数组变量的局限性比较大。

这里我们好好讲讲数组变量和指针。他们有很大的相似，也有不少的区别，首先数组变量是可以赋值给指针的，但是指针是不可以赋值给数组变量的，换句话说，数组变量是一种常量，是不能被赋值的。

我们看一下数组和指针在函数形参下的表现：

```
void PrintValues(const int ia[10])
```

首先我们看如果数组是形参的话，我们要用这样的形式，并且这里声明了大小，实际上这里，这个数组的形参实际上会被编译器改造为一个指针，所以实际上和形参是`const int* a`没有区别，那个中括号中的10是没啥用的。此外，我们还可以利用数组可以给指针赋值的特性，使用指针来为数组传参。

```
void PrintValues(const int *ia,int size)
```

此外我们可以传数组的引用。这时候的那个2是有明确意义的，不能省略的。

```
void PrintValues( int (&ia)[2])
```

[C++ 基础知识一 ——通过引用传递数组](http://www.cnblogs.com/xuhe/p/5704008.html)



计数排序中我们还需要注意一点，就是输入数组和输出数组的大小和索引我们要注意，输入数组是从0索引开始使用的，输出数组也是这样，但是临时数组在计数的时候是从1开始算的，也就是计数为1的算到输出数组的0索引里面。

```c++
void count_sort(int* &inputArr, int len) {
    //首先我们设定一个临时数组，这个临时数组的大小和输入数组中所有元素的最大值有关系
    //我们遍历输入数组，然后我们找出最大值
    int large = -1;
    for (int i = 0; i < len; ++i) {
        if (large < inputArr[i]) {
            large = inputArr[i];
        }
    }
    //然后根据这个最大值创造一个数组，这里我们要注意这个数组的大小
    //我们要让输入数组的最大值与临时数组的最大索引保持一致
    int *temp_count = new int[large + 1];
    //这个计数数组的初始化
    for (int j = 0; j <= large; ++j) {
        temp_count[j] = 0;
    }
    //然后我们进行计数
    for (int k = 0; k < len; ++k) {
        temp_count[inputArr[k]]++;
    }

//    for (int j = 0; j <= large ; ++j) {
//        cout << temp_count[j] << " , ";
//    }
//    cout << endl;
    //然后我们进一步处理临时计数数组，让数组第n位记录输入数组中小于等于n的元素个数
    //处理方法就是不断从临时数组的第一位开始不断让相邻的两个数相加
    for (int l = 1; l <= large; ++l) {
        temp_count[l] = temp_count[l] + temp_count[l - 1];
    }

//    for (int j = 0; j <= large ; ++j) {
//        cout << temp_count[j] << " , ";
//    }
//    cout << endl;

    //建立输出数组
    int *output = new int[len];

    //然后我们遍历输入数组，为输入数组的每一个元素在输出数组中找到一个新的位置
    for (int m = 0; m < len; ++m) {
        //通过查看临时计数数组，给输入元素找在输出元素的位置
        output[temp_count[inputArr[m]]-1] = inputArr[m];
        //因为可能有重复元素，所以我们要在排序之后将计数值-1
        temp_count[inputArr[m]]--;
    }
    delete inputArr;
    inputArr = output;
}
```

计数排序的主要的应用场景是在排序的数比较密集的，不太密集的话会造成空间的浪费。



### 基数排序

这也是一种非比较排序，基数排序和小学生做数字比较大小思路很像。就是一位一位一位比。

基数排序是一种从最小位到最大位不断比较的排序，这个和我们自然的认识可不一样，我们对于每一位的排序必须是稳定排序，也就是说我们在进行高位的排序的时候如果高位一样，就一定要保证低位的顺序。

[稳定排序与不稳定排序](http://www.cnblogs.com/codingmylife/archive/2012/10/21/2732980.html)

> 首先，排序算法的稳定性大家应该都知道，通俗地讲就是能保证排序前2个相等的数其在序列的前后位置顺序和排序后它们两个的前后位置顺序相同。在简单形式化一下，如果Ai = Aj，Ai原来在位置前，排序后Ai还是要在Aj位置前。
>
> 其次，说一下稳定性的好处。排序算法如果是稳定的，那么从一个键上排序，然后再从另一个键上排序，第一个键排序的结果可以为第二个键排序所用。基数排序就是这样，先按低位排序，逐次按高位排序，低位相同的元素其顺序再高位也相同时是不会改变的。另外，如果排序算法稳定，对基于比较的排序算法而言，元素交换的次数可能会少一些。

下面是这个算法的伪代码：

```
//下面进行整数的计数排序从低位到高位进行排序，对不同位数进行稳定排序
radix_sort(A[] , len)
	//我们进行循环，两层循环，一层是遍历数组，一层是遍历数字的每一位，从低到高
	//首先进行位数的遍历
	for i
		do
		//经过改造的插入排序，每次都对其中一位进行插入排序
		insert_sort(A , len , i)
```



### 桶排序

这个是一个感觉有点像哈希的排序，只是排序的时候我们要保证要进行排列的数组的每一位在进行处理之后，产生的新的数字不改变其在数列中的排序。产生的这个数字就是桶的编号，而桶就是一个链表结构，在链表中的元素就是经过桶分类的数列元素，在插入桶的过程中，他依然经过了排序。使得在链表中的元素也是按照某种方式排列的。并且在高位的桶中的每一个元素也“大于”在低位桶中的每一个元素。

桶排序在元素分布均匀的数列排序中表现出色，时间复杂度为n。



## 顺序统计量的选择问题

顺序统计量就是数列中第n大的数，这个数可以是最大值，也可以是最小值，也可以是中位数，顺序统计量的选择我们可以排序之后直接选，也可以使用一些时间复杂度为n的算法。

### 找出最大值和最小值

我们找到最大值和最小值的算法其实就是我们常用的算法。总体的思路就是设定一个变量就是min活着max，然后遍历输入数组，数组中的每一个元素都要和min活着max比较，最后的效果就是让max或者min存着已比较元素中最大或者最小的那个元素。

```
get_min(A[] , len)
	for j <- 0 upto len
		do
		if(min -> A[j])
			then
			min <- A[j]
```

这个的时间复杂度是n。一共进行了n次比较

如果我们需要同时找到最大值和最小值，那就是2n吗，实际上有一种只需要3n/2次比较就可以了。

```
get_min_and_max(A[] , len)
	for j <- 0 upto len j <- j+2
		do
		if A[j] > A[j+1]
			then
			if max < A[j]
				then
				max <- A[j]
			
			if min > A[j+1]
				then
				min <- A[j+1]
		else
			if max < A[j+1]
				then
				max <- A[j+1]
			if min > A[j]
				then
				min <- A[j]
```



我们在算法导论中还发现一个问题，在题目中有一个问题：“我们如何才能找到一个数列中的最小或者第二小的值”，其实最诡异的就是题目还要求进行n+lgn-2次比较。

我们发现使用树状比较可以创造出满足要求的东西，我们举一个例子。

![](http://ww4.sinaimg.cn/large/006tNbRwly1fepr06f9k3j30wo0jg0uv.jpg)

我们使用的方式主要是树状比较排序。对于数的每一层，我们两两分组进行比较，直到只剩下一个根节点，这个就是最大值，一共需要n-1次排序。因为每一层的内容我们需要使用一个数组进行保留。然后我我们做的就是将和最小元素比较过的元素单独拿出来进行一个次比较，找出这些元素中的最小值，比较次数为lgn-1次。



### 随机选择排序---找出第n小的元素

这个是一个比找最大值和最小值都要复杂的算法，整体的思路复用了快速排序算法的内容。我们知道快速排序的平均时间复杂度非常小，所以我们要在当中加入随机化因素。

现在说说随机选择排序的算法思路。这个东西与快速排序有异曲同工之妙，或者说他就是一个进行了一半的快速排序，是一个会提前结束的“快速排序”。我么知道进行快速排序的一次递归之后，整个数组会被分成3个部分。一个是桩变量，一个是小于桩变量的数组，一个是大于桩变量的数组。因为小于桩变量的数组和大于桩变量的数组大小我们都是知道的。假设桩在数组中第i个位置，我们可以证明，桩是第i+1小的数。假设我们要找的是第j小的数，如果j==i+1，那么就说明桩变量就是我们想要的。如果我们发现j\<i+1，那么我们要找的就是小于桩变量的数组的第j小的元素。如果j\>i+1，那么我们就要在大于桩变量的数组中找第j-i-1小的元素。所以说这个也是一个递归函数，而且与快速排序不同的是，这个是单侧，并且会提前停止的递归。递归的条件只有一个，那就是我们找到的桩在快速排序之后的索引，如果这个索引的大小+1和我们要找的第j小的这个j相等，那么就意味着我们找到的第j小的元素，并且递归结束。下面我们实际实现以下这个算法。

```c++
//第一个形参的输入数组，第二个形参为参与随机选择的数组的起始位置，第三个为参与随机选择的数组结束位置
//第四个为我们要找的是当前范围第rank小的元素
//我们借助快速排序从小到大排序
template<class T>
T random_select_fun(T *inputArr, int start, int end, int rank) {
    //我们确定一个递归结束条件，这个if应该永远不会进入的
    if (start > end) {
        cout << "发生了错误" << endl;
        return NULL;
    }


    //我们首先加入随机过程，随机制定start和end之间的数为桩
    //首先我们摇一个种子
    srand(time(0));
    //找出一个桩
    int stake = rand() % (end - start + 1) + start;
    int tmp = inputArr[end];
    inputArr[end] = inputArr[stake];
    inputArr[stake] = tmp;
    stake = end;

    //桩的数值大小
    int stackNum = inputArr[stake];

    //然后进行类似于快速排序的工作，声明两个索引，一个是放在数组的第一位一个是放在-1位
    //数组的扫描索引
    int j;
    //比桩变量小的数组的最大索引，i+1就是桩，i+2就是比桩大的第一个数
    int i = start - 1;

    for (int j = start; j <= end; ++j) {
        //遍历我们要进行扫描和处理的数组
        if (inputArr[j] <= stackNum) {
            //发现有比桩小的数组，我们就把他们放到start和i（包括i）之间，主要是使用交换的方式
            //因为桩还没有换过来，所以i+1就是比桩大的部分。
            i++;
            tmp = inputArr[i];
            inputArr[i] = inputArr[j];
            inputArr[j] = tmp;
        }
    }

    //最后i就是桩所在的位置
    //我们看看这个桩是不是我们需要的
    //这里要注意，我们虽然发现桩是i，但是实际上i索引所对应的排位应该是i-start+1
    if (rank == i - start + 1) {
        return inputArr[i];
    }

    //如果我们要的数的排序比i+1要小，那么就要进行桩左部数组的递归
    if (rank < i - start + 1) {
        return random_select_fun(inputArr, start, i - 1, rank);
    }

    //如果我们要的数的排序比i+1要打，那么就要进行右部的递归
    //我们首先要知道比i小的数在这个部分一共有多少个，也就是在i左面有多少个数，我们让i和start重合，取一个特殊值就知道有i-start个。
    //所以rank要减去一个i还要减去i左边的数rank - (i - start) - 1
    if (rank > i - start + 1) {
        //这里递归调用的形参要好好注意
        return random_select_fun(inputArr, i + 1, end, rank - (i - start) - 1);
    }
}


template<class T>
T random_select(T *inputArr, int len, int rank) {
    return random_select_fun(inputArr, 0, len - 1, rank);
}
```

实现的难点就是关于桩在当前范围的数组中的排序的计算，要考虑随机选择的起始位置，以及递归调用的时候rank这个形参的计算。当+1-1算不清的时候我们可以适当取取特值。

这个算法我们也可以找出最差时间复杂度可以达到n的方法，主要就是在于桩的选取。我们在上面是采用随机的方法找桩，现在我们采用这样一种方式：

- 将数据5个分为一组，最后不足5个的单独分为一组
- 我们对每一组进行插入排序，获得其中位数
- 将所有的中位数再次进行插入排序，再获取中位数
- 将此中位数为桩进行快速排序的一次迭代。
- 判断桩的位置和我们需要元素的排序之间的关系，选取左子数组或者右子数组进行递归。

## 多叉树的实现与表示

我们实现过二叉树，当时的实现有两种问题，一种就是我们没有办法向父节点回溯，还有一个问题就是没有办法接受任意个数的儿子。所以我们我们同辈之前使用链表连接起来，并且提供一个可以指向父节点的指针。我们的节点结构和二叉树的节点结构非常像，但是我们还是要进行一些修成和扩充，但是总体的思路就是：父指针指向父节点，右指针指向儿子节点，左指针指向兄弟节点。所以我们可以看到实际上任何多叉树都可以变成一个二叉树。

这个类的实现首先我们需要注意的就是关于那个“儿子链表”的处理，我们要处理好插入和删除节点的位置问题，要走适当的距离。并且链表还有边界问题。



## 二叉查找树

二叉查找树是一种可以用来查找的二叉树。我们可以在二叉查找树的一个节点中放一个值，也可以放一个键值对（然后我们主要进行键的查找）。二叉查找树的主要的性质就是左子树的（所有值）大小要小于他的父节点，而右子树（所有值）的大小要大于他的父节点。整个查找的过程最坏的时间复杂度和树的高度是一样的。我们可以使用中序遍历可以将二叉查找树中的内容可以按照顺序输出出来。

二叉查找树首先的一些操作就是查找、前趋、以及后继节点的访问，以及最大值最小值的访问。查找的过程是很简单的，我们使用一个指针，从根节点开始遍历，如果我们要找的元素比子树的根大，那指针就往右子树方向走，如果我们要找的元素比子树的根小，那就往左子树走，直到找到我们需要的节点就好了。

子树极大值和极小值的查找也是比较简单的，极大值我们就一路一直往右子树走，直到不能再走了为止，极小值我们就一路一直往左子树走。

任意节点的前趋和后继节点是比较需要想想的，对于一个从小到大排序的序列来说，我们某一个节点的后继节点实际上就是只比这个节点大一个次序的节点。总共有两种情况，一种是当这个节点有右子树的时候，那么后继节点就是此节点右子树的最左节点，也就是右子树的最小值，但是有一个比较特殊的情况，那就是如果这个节点没有右子树怎么办，那么这个时候就要在父节点下文章了，我们需要不断寻找当前节点的祖先节点，使用父指针一直往回走，直到我们找到第一个祖先节点是某一个节点的左子树，那么这个“某一个节点”就是后继节点，也是中序遍历的下一个元素。前继元素和后继元素的方式类似，但是就是稍微“反过来一下就好”。我们首先关注左子树，也就是去找左子树的最大节点，或者说最右节点，如果没有左子树怎么办，我们使用的方法还是不断往当前节点的祖先节点遍历，直到我们发现一个祖先节点是某一个节点的右子树根节点，那么这个“某一个节点”就是我们所说前驱结点。

很难记？其实我们只要记住一个例子，画一画就好，例子一共三层。

8

4 12

2 6 10 14

1 3 5 7 9 11 13 15

我们只要知道最底层是一个奇数列，就好了。然后往上一直取中位数就好了。

为什么我们那么在意后继节点查找呢，因为这个在元素删除的时候要用到。下面我们说一下元素的增加与删除。二叉查找树的增加前半部分的搜索一样，新的节点添加在树的叶子节点。

那删除怎么办，对于二叉搜索树的，我们的删除过程还是比较简单的，其实主要矛盾就是在子树的处理，我们在删除的同时怎么维护整个整个树还保持原来性质，首先如果我们删除的节点没有子树，那就直接删掉就好了。如果有一个子树，那就把连接子树的那个指针给父节点就好了，如果有两个子树，我们要做的就是把这个节点的后继节点（在右子树的根部）替换过来，用后继节点替换当前节点的位置。

我们现在实现一个二叉查找树。我们复用链表二叉树的代码，但是为树节点加上一个父指针，这个父指针是为了方便寻找父节点而设计的。另外，为了展示出树真正的查找方式，实际上我们在二叉搜索树中存的都是键值对，我们是通过键的值来进行数的构造，但是最终的结果当然是获取值。不过我们在这里加以简化，我们没有键值对的结构，只有“键”，为了实现搜索算法，我们写一段函数来查看某一个树节点是不是存在。

这里我们有两个算法是需要拐拐弯的，一个是删除数节点，还有一个是查找树节点的后继节点。这两个都要依据子树的情况进行分配讨论。



