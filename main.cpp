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
