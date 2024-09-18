#include <bits/stdc++.h>
#include "AVLTree.cpp"
#include "RedBlackTree.cpp"
#include "Dictionary.h"
#include "HashTable.cpp"
#include "OpenHashTable.cpp"
#include "OpenHashTable.h"
using namespace std;


double process_file(Dictionary<std::string, int>& dict, const std::string& input_filename) {
    std::ifstream file(input_filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de entrada: " << input_filename << std::endl;
        return 0;
    }

    std::string word;


    // para manipulacao de palavras, utilizei metodos do cctype e algorithm

    // marcador de tempo para calcular execucao completa da ed
    auto start = std::chrono::high_resolution_clock::now();
    while (file >> word) {
        // Remove pontuação exceto hífen em palavras compostas, passando uma condicao
        // metodo remove_if de algorithm
        // metodo ispunct de cctype
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return std::ispunct(c) && c != '-';
        }), word.end());

        // Converter todos os caracteres para minusculo
        // metodo transform de algorithm e tolower de cctype
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty()) {
            if (dict.contains(word)) {
                dict.update(word, dict.get(word) + 1);
            } else {
                dict.insert(word, 1);
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;


    file.close();

    return duration.count();
}

void save_to_file(const Dictionary<std::string, int>& dict, const std::string& output_filename, double time) {
    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída: " << output_filename << std::endl;
        return;
    }

    // Simplesmente chamar o traverse e redirecionar para o arquivo dentro da main
    output_file << "Frequencias de palavras:\n";
    dict.traverse();  // Isso irá imprimir no console. eu redirecionei a saída para o arquivo.
    output_file.close();
    std::cout << "Resultados salvos em " << output_filename << std::endl << "tempo de execucao: " << time << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "como rodar o codigo: " << argv[0] << " tipo_dict arquivo_entrada arquivo_saida > arquivo_saida" << std::endl;
        return 1;
    }

    std::string dictionary_type = argv[1];
    std::string input_filename = argv[2];
    std::string output_filename = argv[3];
    double time;

    if (dictionary_type == "openhash") {
        OpenHashTable<std::string, int> dict;
        time = process_file(dict, input_filename);
        save_to_file(dict, output_filename, time);  
    } else if (dictionary_type == "hash") {
        HashTable<std::string, int> dict;
        time = process_file(dict, input_filename);
        save_to_file(dict, output_filename, time);  
    } else if (dictionary_type == "avl") {
        AVLTree<std::string, int> dict;
        time = process_file(dict, input_filename);
        save_to_file(dict, output_filename, time);  
    } else if (dictionary_type == "redblack") {
        RedBlackTree<std::string, int> dict;
        time = process_file(dict, input_filename);
        save_to_file(dict, output_filename, time);  
    } else {
        std::cerr << "tipo de dicionario desconhecido: " << dictionary_type << std::endl;
        return 1;
    }

    return 0;
}