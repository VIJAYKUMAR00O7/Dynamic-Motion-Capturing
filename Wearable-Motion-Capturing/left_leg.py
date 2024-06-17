import serial
import pygame
import math

# Pygame initialization
pygame.init()
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Human Skeleton Capture")
clock = pygame.time.Clock()

# Serial communication initialization
ser = serial.Serial('COM11', 9600)  # Replace <YOUR_ARDUINO_PORT> with the correct port

# Joint and segment parameters
joint_radius = 50
segment_lengths = [200, 200]  # Lengths of body, legs
segment_thickness = 15

# Fixed circle position for the head
head_x = 400
head_y = 200

# Initial positions of body segments
body_x = head_x
body_y = head_y + joint_radius
left_hand_x = body_x - segment_lengths[0]
left_hand_y = body_y
right_hand_x = body_x + segment_lengths[0]
right_hand_y = body_y
left_leg_x = body_x - segment_lengths[1]
left_leg_y = body_y + segment_lengths[0]
right_leg_x = body_x + segment_lengths[1]
right_leg_y = body_y + segment_lengths[0]

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            ser.close()
            exit()

    # Read data from Arduino
    data = ser.readline().decode('latin-1').strip().split(",")

    if len(data) == 6:
        ax, ay, az, gx, gy, gz = map(int, data)

        # Calculate new position of left leg based on accelerometer data
        left_leg_x += gx // 1000
        left_leg_y += gy // 1000

        # Keep the left leg within the screen boundaries
        left_leg_x = max(left_leg_x, body_x - segment_lengths[1])
        left_leg_x = min(left_leg_x, body_x)
        left_leg_y = max(left_leg_y, body_y + segment_lengths[0])
        left_leg_y = min(left_leg_y, body_y + segment_lengths[0] + segment_lengths[1])

        screen.fill((0, 0, 0))

        # Draw body segments
        pygame.draw.circle(screen, (255, 255, 255), (int(head_x), int(head_y)), joint_radius)
        pygame.draw.line(screen, (255, 255, 255), (body_x, body_y), (left_hand_x, left_hand_y), segment_thickness)
        pygame.draw.line(screen, (228, 255, 255), (body_x, body_y), (right_hand_x, right_hand_y), segment_thickness)
        pygame.draw.line(screen, (255, 61, 48), (body_x, body_y), (left_leg_x, left_leg_y), segment_thickness)
        pygame.draw.line(screen, (255, 255, 255), (body_x, body_y), (right_leg_x, right_leg_y), segment_thickness)

        pygame.display.update()

    clock.tick(30)
