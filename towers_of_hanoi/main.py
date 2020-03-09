tower = {'A':[],'B':[],'C':[]}

def move(a, b):
    #print(tower)
    print("Moving from {} to {}".format(a, b))
    #print("moving {}".format(tower[a].top()))
    tower[b].append(1)
    tower[a].pop()

def hanoi(n, src, dest, aux):
    if n == 1:
        move(src, dest)
    else:
        hanoi(n-1, src, aux, dest)
        move(src, dest)
        hanoi(n-1, aux, dest, src)

tower['A'] = [1,2,3]

hanoi(3, 'A', 'C', 'B')
