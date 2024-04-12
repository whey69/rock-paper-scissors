import pygame
import random

def clamp(val, min, max):
    if val < min:
        return min
    if val > max:
        return max
    return val

class sqr:
    vel = (0,0)
    pos = (0,0)
    width = (0,0)
    rect = None 
    _type = None # 0 is rock, 1 is paper, 2 is scissors
    
    def update(self):
        self.pos = (clamp(self.pos[0] + (self.vel[0]), 0, 1280 - self.width[0]), clamp(self.pos[1] + (self.vel[1]), 0, 720 - self.width[1] - stat))
        
        if (self.pos[0] <= 0 or self.pos[0] >= 1280 - self.width[0]):
            self.vel = (-self.vel[0], self.vel[1])
        if (self.pos[1] <= 0 or self.pos[1] >= 720 - self.width[1] - stat):
            self.vel = (self.vel[0], -self.vel[1])

        self.rect = pygame.rect.Rect(self.pos, self.width)
        col = self.rect.collidelistall([s.rect for s in sqrs])
        if col != None:
            for c in col:
                s = sqrs[c]
                if s._type != self._type:
                    # this is not gonna look good
                    if s._type == 0 and self._type == 1:
                        pass
                    if s._type == 0 and self._type == 2:
                        self._type = 0
                        
                    if s._type == 1 and self._type == 0:
                        self._type = 1
                    if s._type == 1 and self._type == 2:
                        pass
                    
                    if s._type == 2 and self._type == 0:
                        pass
                    if s._type == 2 and self._type == 1:
                        self._type = 2
        
        pygame.draw.rect(disp, ("red" if self._type == 2 else ("white" if self._type == 1 else "gray")), self.rect)
    
    def __init__(self):
        self.vel = (random.uniform(-4, 4), random.uniform(-4, 4))
        self.pos = (random.randint(0, 1275), random.randint(0, 705))
        self.width = (25, 25) # try random stuff until it is nice :3
        self.rect = pygame.rect.Rect(self.pos, self.width)
        self._type = random.randint(0, 2)

disp = pygame.display.set_mode((1280,720))
cloc = pygame.time.Clock()
sqrs = [sqr() for _ in range(250)]
dl = 0
stat = 76
left = [0, 0, 0] # rock, paper, scissors
coun = 0

pygame.font.init()
font = pygame.font.SysFont('consolas.ttf', 72)

pygame.init()

txt = [font.render("rocks: ...;", True, "white"), 
       font.render("papers: ...;", True, "white"),
       font.render("scissors: ...;", True, "white")]
run = True
while run:
    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            run = False
            break
        if e.type == pygame.KEYDOWN:
            if e.key == pygame.K_SPACE:
                sqrs = [sqr() for _ in range(250)]
 
    disp.fill("black")
    left = [0, 0, 0]
    
    for s in sqrs:
        s.update()
        left[s._type] += 1
        
    if(coun >= .25):
        txt = [font.render(f"rocks: {left[0]};", True, "black"), 
            font.render(f"papers: {left[1]};", True, "black"),
            font.render(f"scissors: {left[2]};", True, "black")]
        coun = 0
    
    pygame.draw.rect(disp, "gray", (0, 720 - stat, 1280 * (1/3), 720 - (720 - stat)))
    pygame.draw.rect(disp, "white", ((1280 * (1/3)), 720 - stat, 1280 * (2/3), 720 - (720 - stat)))
    pygame.draw.rect(disp, "red", ((1280 * (2/3)), 720 - stat, 1280, 720 - (720 - stat)))
    disp.blit(txt[0], (10, 720 - stat))
    disp.blit(txt[1], ((1280 * (1/3)) + 10, 720 - stat))
    disp.blit(txt[2], ((1280 * (2/3)) + 10, 720 - stat))
    
    pygame.display.flip()   
    dl = cloc.tick(60) / 1000
    coun += dl
