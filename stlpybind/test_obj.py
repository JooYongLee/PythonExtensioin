import MyData
from MyData import mytest, modify, readfile
data = MyData.CModelData()
print(data.getName())
data.setName("Sdfsdf")
print(data.getName())
dd = mytest()
print(dd)
print(dd.getName())

B = modify()

print(B)
print(len(B))
aa = readfile()
# print(aa)
for p in aa:
    print(p.getName())