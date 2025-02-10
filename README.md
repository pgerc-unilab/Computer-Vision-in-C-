![BannerProject](https://raw.githubusercontent.com/pgerc-unilab/Computer-Vision-in-C-/b7f1ebeba18af21a1579bf65d867a5cf6a2ad6b0/Banner.svg)

[![ProjectC++](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1RhDMTi2gLUh-TgMtp9qvvmsSRM4wq80y?usp=sharing)
---

Este projeto demonstra como baixar uma imagem da web, convertê-la de um formato colorido (3 canais) para escala de cinza (1 canal) usando a biblioteca OpenCV em C++.

## Teoria dos Canais de Cores

Uma imagem colorida digital é composta por três canais de cores: **Vermelho (Red)**, **Verde (Green)** e **Azul (Blue)**, conhecidos como **RGB**. Cada canal representa a intensidade de uma cor primária em cada pixel da imagem. A combinação desses três canais produz a imagem colorida final.

- **Canal Vermelho (R)**: Contém a intensidade da cor vermelha em cada pixel.
- **Canal Verde (G)**: Contém a intensidade da cor verde em cada pixel.
- **Canal Azul (B)**: Contém a intensidade da cor azul em cada pixel.

Cada pixel em uma imagem colorida é representado por três valores (R, G, B), que variam de 0 a 255 em imagens de 8 bits. Por exemplo, um pixel com valores (255, 0, 0) é vermelho puro, enquanto (0, 255, 0) é verde puro.

### Conversão para Escala de Cinza

A conversão de uma imagem colorida (3 canais) para escala de cinza (1 canal) envolve a combinação dos três canais de cores em um único canal. A escala de cinza representa a luminosidade de cada pixel, onde 0 é preto e 255 é branco.

### Por que Converter para Escala de Cinza?

A conversão para escala de cinza é uma técnica comum em visão computacional por várias razões:
1. **Redução de Complexidade**: Trabalhar com um único canal é computacionalmente mais eficiente do que processar três canais.
2. **Pré-processamento**: Muitos algoritmos de visão computacional, como detecção de bordas ou reconhecimento de padrões, funcionam melhor com imagens em escala de cinza.
3. **Redução de Ruído**: A conversão para escala de cinza pode ajudar a reduzir o ruído em imagens coloridas.

