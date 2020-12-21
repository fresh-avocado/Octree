# Observaciones

- El informe tiene 7 páginas, ya que 1 página tiene solo imágenes.
- Note que a veces la imagen resultante puede ser un rectangulo comprimido y aislado hacia un lado. Esto es debido a el área resultande de hacer un corte en el cubo original, tiene dimensiones más pequeñas o simplemente diferentes a las de una imagen regular.
- Las imagenes que salen del octree son rojas debido a que usamos `CImg<float>` y asignamos un valor de 255, lo correcto seria utilizar `CImg<char>` para que cuando le asignemos 255 sea el color blanco, pero al hacer esto teniamos problemas.