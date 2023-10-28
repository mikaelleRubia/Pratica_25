#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Usuario {
private:
    string nome_usuario;
    string nome;
    vector<Usuario*> seguidores;
    vector<Usuario*> seguindo;

public:
    Usuario(string nome_usuario, string nome) {
        this->nome_usuario = nome_usuario;
        this->nome = nome;
    }

    string getNomeUsuario() {
        return nome_usuario;
    }

    string getNome() {
        return nome;
    }

    vector<Usuario*> getSeguidores() {
        return seguidores;
    }

    vector<Usuario*> getSeguindo() {
        return seguindo;
    }

    void setNomeUsuario(string nome_usuario) {
        this->nome_usuario = nome_usuario;
    }

    void setNome(string nome) {
        this->nome = nome;
    }

    void postar_tweet(string tweet) {
        cout << nome_usuario << " postou um tweet: " << tweet << endl;
    }

    void seguir(Usuario* usuario) {
        seguindo.push_back(usuario);
        usuario->seguidores.push_back(this);
    }

    vector<string> receber_feed() {
        vector<string> feed;
        for (Usuario* usuario : seguindo) {
            feed.push_back(usuario->getNomeUsuario() + ": Tweet do usuario " + usuario->getNomeUsuario());
        }
        return feed;
    }
};

class Tweet {
private:
    Usuario* autor;
    string conteudo;
    time_t data_criacao;

public:
    Tweet(Usuario* autor, string conteudo) {
        this->autor = autor;
        this->conteudo = conteudo;
        this->data_criacao = time(nullptr);
    }

    Usuario* getAutor() {
        return autor;
    }

    string getConteudo() {
        return conteudo;
    }

    string getDataCriacao() {
        return asctime(localtime(&data_criacao));
    }
};

class RedeSocial {
private:
    vector<Usuario*> usuarios;
    vector<Tweet*> tweets;

public:
    void registrar_usuario(string nome_usuario, string nome) {
        Usuario* novoUsuario = new Usuario(nome_usuario, nome);
        usuarios.push_back(novoUsuario);
    }

    Usuario* buscar_usuario(string nome_usuario) {
        for (Usuario* usuario : usuarios) {
            if (usuario->getNomeUsuario() == nome_usuario) {
                return usuario;
            }
        }
        return nullptr;
    }

    vector<Usuario*> listar_usuarios() {
        return usuarios;
    }

    vector<Tweet*> listar_tweets() {
        return tweets;
    }

    void adicionar_tweet(Tweet* tweet) {
        tweets.push_back(tweet);
    }

    // Getters
    vector<Usuario*> getUsuarios() {
        return usuarios;
    }

    vector<Tweet*> getTweets() {
        return tweets;
    }

    // Setters
    void setUsuarios(vector<Usuario*> usuarios) {
        this->usuarios = usuarios;
    }

    void setTweets(vector<Tweet*> tweets) {
        this->tweets = tweets;
    }
};

int main() {
    RedeSocial redeSocial;
    int opcao;

    do {
        cout << "----- MENU -----" << endl;
        cout << "1. Registrar usuário" << endl;
        cout << "2. Postar tweet" << endl;
        cout << "3. Seguir usuario" << endl;
        cout << "4. Ver feed de tweets" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                string nome_usuario, nome;
                cout << "Digite o nome de usuario: ";
                cin >> nome_usuario;
                cout << "Digite o nome: ";
                cin >> nome;
                redeSocial.registrar_usuario(nome_usuario, nome);
                cout << "Usuario registrado com sucesso!" << endl;
                break;
            }
            case 2: {
                string nome_usuario, tweet;
                cout << "Digite o nome de usuario: ";
                cin >> nome_usuario;
                cout << "Digite o tweet: ";
                cin.ignore();
                getline(cin, tweet);
                Usuario* usuario = redeSocial.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    usuario->postar_tweet(tweet);
                    cout << "Tweet postado com sucesso!" << endl;
                } else {
                    cout << "Usuario nao encontrado." << endl;
                }
                break;
            }
            case 3: {
                string nome_usuario_seguidor, nome_usuario_seguindo;
                cout << "Digite o nome de usuario do seguidor: ";
                cin >> nome_usuario_seguidor;
                cout << "Digite o nome de usuario do usuário a ser seguido: ";
                cin >> nome_usuario_seguindo;
                Usuario* seguidor = redeSocial.buscar_usuario(nome_usuario_seguidor);
                Usuario* seguindo = redeSocial.buscar_usuario(nome_usuario_seguindo);
                if (seguidor != nullptr && seguindo != nullptr) {
                    seguidor->seguir(seguindo);
                    cout << "Usuario seguido com sucesso!" << endl;
                } else {
                    cout << "Usuario(s) nao encontrado(s)." << endl;
                }
                break;
            }
            case 4: {
                string nome_usuario;
                cout << "Digite o nome de usuario: ";
                cin >> nome_usuario;
                Usuario* usuario = redeSocial.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    vector<string> feed = usuario->receber_feed();
                    cout << "Feed de tweets de " << nome_usuario << ":" << endl;
                    for (string tweet : feed) {
                        cout << tweet << endl;
                    }
                } else {
                    cout << "Usuario nao encontrado." << endl;
                }
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }

        cout << endl;
    } while (opcao != 0);

    return 0;
}