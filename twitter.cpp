#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <limits>

using namespace std;

class Usuario;
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
class Usuario {
private:
    string nome_usuario;
    string nome;
    vector<Usuario*> seguidores;
    vector<Usuario*> seguindos;
    vector<Tweet*> tweets;

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
        return seguindos;
    }

    void setNomeUsuario(string nome_usuario) {
        this->nome_usuario = nome_usuario;
    }

    void setNome(string nome) {
        this->nome = nome;
    }

    void postar_tweet(string str) {
        Tweet* novoTweet = new Tweet(this, str);
        cout << nome_usuario << " postou um tweet: " << str << endl;
        tweets.push_back(novoTweet);
    }

    void seguir(Usuario* usuario) {
        seguindos.push_back(usuario);
        usuario->seguidores.push_back(this);
    }

    void Listar_Seguidores_feed() {
        cout << "-------------- FEED DOS USUARIOS QUE SIGO --------------" << endl;
        for(Usuario *u : seguindos) {
            for(Tweet *tweet : u->tweets) {
                cout << "Autor: " << tweet->getAutor()->getNomeUsuario() <<
                    "\nTweet: " << tweet->getConteudo() <<
                    "\nPostado em: " << tweet->getDataCriacao() << endl;
                cout << "------------------------------------------" << endl;
            }
        }
    }
};



class RedeSocial {
private:
    vector<Usuario*> usuarios;
    vector<Tweet*> tweets;

public:
    void registrar_usuario(string nome_usuario, string nome) {
        Usuario* novoUsuario = new Usuario(nome_usuario, nome);
        for(Usuario *u : usuarios) {
            if(novoUsuario->getNomeUsuario() == u->getNomeUsuario()) {
                cout << "Usuario ja existe!" << endl;
                return;
            }
        }
        usuarios.push_back(novoUsuario);
        cout << "Usuario registrado com sucesso!" << endl;
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

    void listar_tweets() {
        cout << "\n------------------------------------------" << endl;
        for(Tweet *tweet : tweets) {
            cout << "Autor: " << tweet->getAutor()->getNomeUsuario() <<
                "\nTweet: " << tweet->getConteudo() <<
                "\nPostado em: " << tweet->getDataCriacao() << endl;
            cout << "------------------------------------------" << endl;

        }
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

void pause()
{
    cin.ignore();
    cout << "\nPressione a tecla Enter para continuar...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void limpaTela()
{
    cin.clear();

    // Verifica se a variável de ambiente WINDIR está definida (ambiente Windows)
    const char *windir = getenv("WINDIR");

    if (windir != nullptr && strlen(windir) > 0)
    {
        // Se estiver definida, estamos no Windows, então use "cls"
        system("cls");
    }
    else
    {
        // Caso contrário, estamos em um ambiente Unix/Linux, use "clear"
        system("clear");
    }
}

int main() {
    RedeSocial redeSocial;
    int opcao;

    do {
        limpaTela();
        cout << "----- MENU -----" << endl;
        cout << "1. Registrar usuário" << endl;
        cout << "2. Postar tweet" << endl;
        cout << "3. Seguir usuario" << endl;
        cout << "4. Ver tweets postados" << endl;
        cout << "5. Ver feed de tweets" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                limpaTela();
                cout << "----- REGISTRAR USUARIO -----" << endl;
                string nome_usuario, nome;
                cout << "Digite o nome de usuario: ";
                cin >> nome_usuario;
                cout << "Digite o nome: ";
                cin >> nome;
                redeSocial.registrar_usuario(nome_usuario, nome);
                pause();
                break;
            }
            case 2: {
                limpaTela();
                cout << "----- POSTAR TWEET -----" << endl;
                string nome_usuario, tweet;
                cout << "Digite o nome de usuario: ";
                cin >> nome_usuario;
                cout << "Digite o tweet: ";
                cin.ignore();
                getline(cin, tweet);
                Usuario* usuario = redeSocial.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    usuario->postar_tweet(tweet);
                    redeSocial.adicionar_tweet(new Tweet(usuario, tweet));
                    cout << "Tweet postado com sucesso!" << endl;
                } else {
                    cout << "Usuario nao encontrado." << endl;
                }
                pause();
                break;
            }
            case 3: {
                limpaTela();
                cout << "----- SEGUIR USUÁRIO -----" << endl;
                string nome_usuario_seguidor, nome_usuario_seguindo;
                cout << "Digite o nome do usuário: ";
                cin >> nome_usuario_seguidor;
                cout << "Digite o nome do usuário a ser seguido: ";
                cin >> nome_usuario_seguindo;
                Usuario* seguidor = redeSocial.buscar_usuario(nome_usuario_seguidor);
                Usuario* seguindo = redeSocial.buscar_usuario(nome_usuario_seguindo);
                if (seguidor != nullptr && seguindo != nullptr) {
                    seguidor->seguir(seguindo);
                    cout << "Usuario seguido com sucesso!" << endl;
                } else {
                    cout << "Usuario(s) nao encontrado(s)." << endl;
                }
                pause();
                break;
            }
            case 4: {
                limpaTela();
                cout << "----- TWEETS POSTADOS -----" << endl;
                redeSocial.listar_tweets();
                pause();
                break;
            }
            case 5: {
                limpaTela();
                cout << "----- FEED DE TWEETS -----" << endl;
                string nome_usuario;
                cout << "Digite o nome de usuario: ";
                cin >> nome_usuario;
                Usuario* usuario = redeSocial.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    usuario->Listar_Seguidores_feed();
                } else {
                    cout << "Usuario nao encontrado." << endl;
                }
                pause();
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                limpaTela();
                cout << "Opcao invalida. Tente novamente." << endl;
                pause();
                break;
        }

        cout << endl;
    } while (opcao != 0);

    return 0;
}