ss= raw_input().lower();
dic= ['a','o','y','e','u','i'];
ans= "";
for c in ss:
    if c in dic: continue  
    else: ans= ans+'.'+c
print ans;
