import pygame,sys, time
from pygame import font

pygame.init()
pygame.display.set_caption('Sudoku')
size = width, height = 900, 900

bc_color = 200, 200, 200
fg_color = 0,0,0

screen = pygame.display.set_mode(size)

font_rend = pygame.font.Font(font.match_font('ibmplexmono'), 50)
message = font_rend.render("9", True, fg_color)

w, h = 9, 9;
Game = [[0 for x in range(w)] for y in range(h)]


def valid(n, x,y):

    for i in range (0,9):
        if Game[x][i] == n:
            return False
        if Game[i][y] == n:
            return False
    
    sqrx, sqry = x//3, y//3
    freq = set(())

    for i in range(0,3):
        for j in range(0,3):
            freq.add(Game[(sqrx*3)+i][(sqry*3)+j])
    
    if(n in freq):
        return False

    return True

def solved():
    for i in range(0,9):
        for j in range(0,9):
            if Game[i][j] == 0:
                return False
    return True

def solve(x,y):

    if x >= 9:
        x=0
        y += 1

    if solved():
        return True

    if Game[x][y] != 0:
        return solve(x+1, y)

    for i in range(1,10):
        if valid(i, x,y):
            Game[x][y] = i
            draw_game()
            #time.sleep(0.1)
            if solve(x+1, y):
                return True

    Game[x][y] = 0
    return False
        

def draw_game():
    screen.fill(bc_color)

    for i in range(0,width, int(width/9)):
        thickness = 2

        if i%(int(width/9)*3) == 0:
            thickness = 5

        pygame.draw.line(screen, fg_color, (0,i),(width,i), thickness) 

    for i in range(0,height, height//9):
        thickness = 2

        if i%(int(height/9)*3) == 0:
            thickness = 5

        pygame.draw.line(screen, fg_color, (i,0),(i,height), thickness) 
    
    for i in range(0, width, width//9):
        for j in range(0, height, height//9):

            message = font_rend.render(str(Game[i//(width//9)][j//(height//9)]), True, fg_color)
            screen.blit(message, (i + 30, j + 20))
    
    pygame.display.flip()

started = False

while not started:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

        if event.type == pygame.KEYDOWN:
            started = True

        if event.type == pygame.MOUSEBUTTONDOWN:
            x,y = pygame.mouse.get_pos()
            Game[x//(width//9)][y//(height//9)] = (Game[x//(width//9)][y//(height//9)] + 1)%10

    draw_game()

solve(0,0)


while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

    draw_game()
