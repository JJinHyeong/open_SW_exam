import pygame
from pygame.rect import *
import random

def restart():
    global isGameOver, score
    isGameOver = False
    score = 0
    for i in range(len(star)):
        recStar[i].y = -1


def eventProcess():
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()

            if event.key == pygame.K_LEFT:
                move.x = -2
            if event.key == pygame.K_RIGHT:
                move.x = 2
            if event.key == pygame.K_UP:
                move.y = -2
            if event.key == pygame.K_DOWN:
                move.y = 2
            if event.key == pygame.K_SPACE:
                restart()

        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                move.x = 0
            elif event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                move.y = 0


def movePlayer():
    if not isGameOver:
        recPlayer.x += move.x
        recPlayer.y += move.y
    if recPlayer.x < 0:
        recPlayer.x = 0
    if recPlayer.x > SCREEN_WIDTH - recPlayer.width:
        recPlayer.x = SCREEN_WIDTH - recPlayer.width
    if recPlayer.y < 0:
        recPlayer.y = 0
    if recPlayer.y > SCREEN_HEIGHT - recPlayer.height:
        recPlayer.y = SCREEN_HEIGHT - recPlayer.height
    SCREEN.blit(player, recPlayer)


def timeDelay500ms():
    global time_delay_500ms
    if time_delay_500ms > 5:
        time_delay_500ms = 0
        return True
    time_delay_500ms += 1
    return False


def makeStar():
    if isGameOver:
        return
    if timeDelay500ms():
        idex = random.randint(0, len(star) - 1)
        if recStar[idex].y == -1:
            recStar[idex].x = random.randint(0, SCREEN_WIDTH)
            recStar[idex].y = 0


def moveStar():
    makeStar()
    for i in range(len(star)):
        if recStar[i].y == -1:
            continue
        if not isGameOver:
            recStar[i].y += 1
        if recStar[i].y > SCREEN_HEIGHT:
            recStar[i].y = 0
        SCREEN.blit(star[i], recStar[i])


def CheckCollision():
    global score, isGameOver
    if isGameOver:
        return
    for rec in recStar:
        if rec.y == -1:
            continue
        if rec.top < recPlayer.bottom \
                and recPlayer.top < rec.bottom \
                and rec.left < recPlayer.right \
                and recPlayer.left < rec.right:
            print('충돌')
            isGameOver = True
            break
    score += 1


def blinking():
    global time_dealy_4sec, toggle
    time_dealy_4sec += 1
    if time_dealy_4sec > 40:
        time_dealy_4sec = 0
        toggle = ~toggle
    return toggle


def setText():
    mFont = pygame.font.SysFont("arial", 40, True, False)
    SCREEN.blit(mFont.render(
        f'score : {score}', True, 'green'), (10, 10, 0, 0))

    if isGameOver and blinking():
        SCREEN.blit(mFont.render(
            'Game Over!!', True, 'red'), (240, 300, 0, 0))
        SCREEN.blit(mFont.render(
            'press SPACE - Restart', True, 'red'), (200, 340, 0, 0))


# 변수초기화
isActive = True
SCREEN_WIDTH = 720
SCREEN_HEIGHT = 700
move = Rect(0, 0, 0, 0)
time_delay_500ms = 0
time_dealy_4sec = 0
toggle = False
score = 0
isGameOver = False

# 스크린생성
pygame.init()
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('C언어 피하기')

# player 생성
player = pygame.image.load('C:/wuwang.png')
player = pygame.transform.scale(player, (50, 50))
recPlayer = player.get_rect()
recPlayer.centerx = (SCREEN_WIDTH / 2)
recPlayer.centery = (SCREEN_HEIGHT / 2)
# 유성 생성
star = [pygame.image.load('C:/C.png') for i in range(30)]
recStar = [None for i in range(len(star))]
for i in range(len(star)):
    star[i] = pygame.transform.scale(star[i], (25, 25))
    recStar[i] = star[i].get_rect()
    recStar[i].y = -1

clock = pygame.time.Clock()


while isActive:
    # 화면 지움
    SCREEN.fill((0, 0, 0))
    # 이벤트처리
    eventProcess()
    # 플레이어 이동
    movePlayer()
    # 유성 생성 및 이동
    moveStar()
    # 충돌 확인
    CheckCollision()
    # text업데이트
    setText()
    # 화면 재설정
    pygame.display.flip()
    clock.tick(100)