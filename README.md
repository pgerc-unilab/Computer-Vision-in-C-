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

<img src="https://raw.githubusercontent.com/pgerc-unilab/Computer-Vision-in-C-/refs/heads/main/circle/colors.png" width="30%"> <img src="https://raw.githubusercontent.com/pgerc-unilab/Computer-Vision-in-C-/refs/heads/main/circle/colorscinza.png" width="30%">


### Por que Converter para Escala de Cinza?

A conversão para escala de cinza é uma técnica comum em visão computacional por várias razões:
1. **Redução de Complexidade**: Trabalhar com um único canal é computacionalmente mais eficiente do que processar três canais.
2. **Pré-processamento**: Muitos algoritmos de visão computacional, como detecção de bordas ou reconhecimento de padrões, funcionam melhor com imagens em escala de cinza.
3. **Redução de Ruído**: A conversão para escala de cinza pode ajudar a reduzir o ruído em imagens coloridas.

## Vamos ao Código

```cpp
#include <iostream> // Entrada e saída
#include <string>   // Manipulação de strings
#include <sstream>  // Streams de memória
#include <curl/curl.h> // Biblioteca cURL para download de URLs
#include <opencv2/imgproc.hpp> // Processamento de imagens OpenCV
#include <opencv2/opencv.hpp> // OpenCV

using namespace cv; // Usando o namespace cv para facilitar o código

// Callback para escrever os dados recebidos pelo cURL em um buffer de string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Função para baixar uma imagem de uma URL
std::vector<uchar> downloadImage(const std::string& url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());       // Define a URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Define a função de callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Define o buffer para escrita
        res = curl_easy_perform(curl);                          // Executa o download
        curl_easy_cleanup(curl);                               // Limpa os recursos do cURL
        if(res != CURLE_OK) {                                  // Verifica erros
            std::cerr << "curl_easy_perform() falhou: " << curl_easy_strerror(res) << std::endl;
            return {};
        }
    } else {
        std::cerr << "curl_easy_init() falhou" << std::endl;
        return {};
    }

    std::vector<uchar> imageData(readBuffer.begin(), readBuffer.end()); // Converte a string para um vetor de uchar
    return imageData;
}

int main() {
    std::string imageUrl = "https://raw.githubusercontent.com/leonardoalvessousa/RaspAsmList"; // URL da imagem
    std::vector<uchar> imageData = downloadImage(imageUrl);          // Baixa a imagem

    if (imageData.empty()) {                                        // Verifica se o download falhou
        std::cerr << "Falha ao baixar a imagem." << std::endl;
        return -1;
    }

    Mat color = imdecode(imageData, IMREAD_COLOR);                 // Decodifica a imagem colorida
    if (color.empty()) {                                           // Verifica se a decodificação falhou
        std::cerr << "Falha ao decodificar a imagem." << std::endl;
        return -1;
    }

    Mat gray;                                                      // Converte para escala de cinza
    cvtColor(color, gray, COLOR_BGR2GRAY);

    imwrite("imagem_baixada.jpg", color);                           // Salva a imagem colorida
    imwrite("imagem_baixada_cinza.jpg", gray);                      // Salva a imagem em tons de cinza

    return 0;
}
```

## Como Executar o Projeto

1. **Compilar o Código**: Use o comando abaixo para compilar o código C++:

```bash
g++ teste.cpp -o teste pkg-config --cflags --libs opencv4 -lcurl
``` 

2. **Executar o Programa**: Após a compilação, execute o programa:

```bash
./teste
```

## Conclusão

Este projeto ilustra como baixar, processar e converter imagens coloridas para escala de cinza usando C++ e OpenCV. A conversão para escala de cinza é uma técnica fundamental em visão computacional, frequentemente usada como etapa de pré-processamento em diversas aplicações.

### Agradecimentos

_Agradecemos à comunidade *Open Source* pelo desenvolvimento e manutenção de ferramentas essenciais, que foram fundamentais para a realização deste projeto!_

## Referências

OPENCV. *OpenCV: Open Source Computer Vision Library*. 2023. Disponível em: <https://opencv.org/>. Acesso em: 11 fev. 2025.

---

![BannerProject](https://raw.githubusercontent.com/pgerc-unilab/Computer-Vision-in-C-/70f123aa93daccb7e1c6c9c750984e0cf7f79a2d/Banner_final.svg)
