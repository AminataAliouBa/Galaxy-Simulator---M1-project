import pygame
import random
import math
from pygame import Vector2
import cppcore

WIDTH, HEIGHT = 800, 800
G = 1e-2
THETA = 1
DT = 10
NUM_PARTICLES = 10000
CENTER_MASS = 1e3
CENTER = Vector2(WIDTH//2, HEIGHT//2)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Barnes-Hut Galaxy")
clock = pygame.time.Clock()

def generate_spiral_galaxy(n, CENTER, arms=2, arm_length=300):
    particles = []
    for _ in range(n):
        angle = random.uniform(0, 2*3.14159*arms)
        radius = random.uniform(10, arm_length)
        x = CENTER.x + radius * math.cos(angle)
        y = CENTER.y + radius * math.sin(angle)
        speed = math.sqrt(G * 1 * 1e3 / (radius + 1e-3))
        vx = -speed * math.sin(angle)
        vy = speed * math.cos(angle)
        p = cppcore.Particle(1.0, x, y, vx, vy)
        particles.append(p)
    return particles

def force_from_center(p):
    dx = CENTER.x - p.position.x
    dy = CENTER.y - p.position.y
    dist = math.hypot(dx, dy) + 1e-5
    F = G * p.mass * CENTER_MASS / dist**2
    angle = math.atan2(dy, dx)
    fx = math.cos(angle) * F
    fy = math.sin(angle) * F
    p.net_force.x += fx
    p.net_force.y += fy

particles = generate_spiral_galaxy(NUM_PARTICLES, CENTER)

root_quad = cppcore.Quad(0, 0, WIDTH, HEIGHT)
root = cppcore.Quadtree(root_quad)
for p in particles:
    root.insert(p)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((0,0,0))

    for p in particles:
        p.reset_force()
        f = root.compute_force(p, THETA, G)
        f1 = force_from_center(p)
        if f is None:
            res=f1
        elif f1 is None:
            res = f
        else:
            res = cppcore.Vec2((f.x+f1.x), (f.y+f1.y))
        p.net_force.x = p.net_force.x+res.x
        p.net_force.y = p.net_force.y+res.y

    for p in particles:
        p.update_position(DT)

    root = cppcore.Quadtree(root_quad)
    for p in particles:
        root.insert(p)

    for p in particles:
        pygame.draw.circle(screen, (255,255,255), (int(p.position.x), int(p.position.y)), 2)

    pygame.display.flip()
    clock.tick(1000)

pygame.quit()
