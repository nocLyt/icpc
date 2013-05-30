
"""分配人乘车时，保证整除不会遗漏人，我们可以增加一个偏移值。保证整除出来的都是正解
    比如此题: a表示的是 一组只有一个人的组数, b表示的一组有两个人的组数，一个车最多乘4个人。 
    偏移值= 3
"""

input()
s= map(int, raw_input().split(' '));
a, b, c, d= [s.count(i) for i in range(1,5)]
print b/2+c+d+ (max(0,a-c)+3+b%2*2 )/4   

    
