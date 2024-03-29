def filtering (li):
    print(list(filter(lambda x:x%2==0,li)))

filtering([1,2,3,4,5,6,7,8])

# touple in care primul elem sunt cele care respecta cond si restul care nu

def selecting(li, f):
    li1=list(filter(lambda x:f(x), li))
    li2=list(filter(lambda x: not f(x), li))
    print((li1,li2))


def selecting(li, f):
    li1=set(filter(lambda x:f(x), li))
    li2= li - li1
    print((li1,li2))

selecting({1,2,3,4,5,6,7,8}, lambda x:x%2==0)


import functools as f

def display(li):
    return list(f.reduce(lambda acc, x: acc+[x] if len(x) < 3 else acc, li, []))

print(display(["ana", "are", "a", "3", "ananannana"]))

def sorting (li):
    return list(f.reduce(lambda acc, x: ,li,[]))