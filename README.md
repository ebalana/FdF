# FdF
> Proyecto de la escuela 42 desarrollado por Ernest Balañá

## Descripción
**fdf** es un visualizador de wireframes en 3D que permite representar mapas en 2D con coordenadas y alturas como un modelo isométrico. El objetivo principal del proyecto es familiarizarse con el uso de la **gráfica en 2D usando la biblioteca MLX42**, así como aprender a manipular coordenadas, proyecciones y transformaciones geométricas. Este proyecto fue desarrollado como parte del currículo de la escuela 42.

## Características
- Lectura de mapas en formato .fdf con coordenadas X, Y, Z
- Representación gráfica en proyección isométrica
- Trazado de líneas mediante el algoritmo de Bresenham
- Uso de la biblioteca gráfica MLX42
- Soporte para rotaciones, zoom y desplazamiento del modelo
- Representación de alturas mediante escala de colores
- Manejo de eventos de teclado para interacción en tiempo real
- Gestión de errores para entradas inválidas y archivos corruptos

## 🛠️ Instalación
```bash
git clone https://github.com/ebalana/Minishell.git
cd minishell
make
./fdf maps/42.fdf
```

## Hooks
- `ESC`: Salir del programa
- `Flechas`: Mover la vista  (arriba/abajo/izquierda/derecha)
- `+/-`: Zoom in/out
- `W/S`: Aumentar/disminuir altura de los puntos (elevación)
- `R`: Resetear vista
- `1/2`: Rotar en eje X (α - alpha)
- `T`: Rotar en eje Y (β - beta)
- `Y`: Rotar en eje Z (γ - gamma)
- `I`: Cambiar proyección (isométrica/paralela)
- `U`: Cambiar modo de proyección alternativo (2D)

## Uso
- `./fdf maps/42.fdf`

<img width="1578" height="946" alt="Screenshot from 2026-06-06 15-32-22" src="https://github.com/user-attachments/assets/3b2da0e4-8d4b-4373-8d8b-c4618e93d0f8" />

- `./fdf maps/pylone.fdf`

<img width="1578" height="946" alt="Screenshot from 2026-06-06 15-35-37" src="https://github.com/user-attachments/assets/fb0d2023-8a9d-466f-94b3-ac1fa9872ecc" />

- `./fdf maps/t2.fdf`

<img width="1578" height="946" alt="Screenshot from 2026-06-06 15-38-10" src="https://github.com/user-attachments/assets/ba1f2774-0b82-46b0-a3f5-0360fa43546e" />

