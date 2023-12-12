#пример сжатия изображение с использованием анализа главных компонентов

import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import numpy as np
from sklearn.decomposition import PCA

#загружаем изображение и выводим его данные
img = mpimg.imread('cat_img_1024_1024.jpg')
print(img.shape) #(200, 246, 3) = 00x246 пикселей и 3 канала цвета

# Для подготовки изображения к анализу с помощью метода главных компонент (PCA),
# необходимо преобразовать изображение в одномерный массив

img_r = np.reshape(img, (1024, 1024*3) )

#запускаем PCA с 32 главными компонентамиm
pca = PCA(32)
pca.fit(img_r)
img_transformed = pca.transform(img_r)
print(np.sum(pca.explained_variance_ratio_))

#обратное преобразование изображения и его выывод
temp = pca.inverse_transform(img_transformed)
temp = np.reshape(temp, (1024, 1024, 3))

# When single channel float image is passed to imshow it gets normalized to range [0,1] before display. This does not happen for RGB images.
plt.imshow(temp.astype('uint8'))
plt.show()

# temp = (temp * 255).astype(np.uint8)
# plt.imsave('transformed_cat_img_2.png', temp)