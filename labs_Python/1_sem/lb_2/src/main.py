import PIL
from PIL import Image, ImageDraw

def triangle(img, x1, y1, x2, y2, x3, y3, thickness, color, fill_color):
    points = [(x1, y1), (x2, y2), (x3, y3)]
    draw = ImageDraw.Draw(img)
    if fill_color:
        draw.polygon(points, fill=tuple(fill_color), width=thickness, outline=tuple(color))
    else:
        draw.polygon(points, width=thickness, outline=tuple(color))
    return img
    
def change_color(img, color):
    img2 = Image.new(img.mode, img.size, None)
    img2.paste(img, (0,0))
    colors = {}
    color = tuple(color)
    for i in range(img2.width):
        for j in range(img2.height):
            if img2.getpixel((i, j)) in colors:
                colors[img2.getpixel((i, j))] +=1
            else:
                colors[img2.getpixel((i, j))] = 1
    orig_color = max(colors, key = colors.get)
    for i in range(img2.width):
        for j in range(img2.height):
            if img2.getpixel((i, j)) == orig_color:
                img2.putpixel((i, j), color)
    return img2


def collage(img, N, M):
    x, y = img.size
    arg = img.crop( (0, 0, x, y) )
    img = Image.new( "RGB", (x * M, y * N) )
    x1 = 0
    y1 = 0
    flag = 1
    for i in range(N * M):
        if flag > M:
            flag = 1
            y1 = y1 + y
            x1 = 0
        img.paste(arg, (x1, y1))
        x1 = x1 + x
        flag += 1
    return img
