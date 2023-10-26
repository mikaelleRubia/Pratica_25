#include <iostream>
#include <vector>

using namespace std;

class Tweet;


class Usuario{
    private:
        string nome;
        string nome_usuario;
        vector<Usuario> seguidores;
        vector<Usuario> seguindo;


    public:
        Usuario();
        Usuario(string nome, string cpf) {this->nome = nome; this->nome_usuario = nome_usuario;}

        string getNome(){ return nome; }
        void setNome(string nome) { this->nome = nome; }

        string getNome_usuario(){ return nome_usuario; }
        void setNome_usuario(string nome_usuario) { this->nome_usuario = nome_usuario; }

        vector<Usuario> getSeguidores() { return seguidores; }
        void setSeguidores(vector<Usuario> _seguidores) { seguidores = _seguidores; }

        vector<Usuario> getSeguindo() { return seguindo; }
        void setSeguindo(vector<Usuario> _seguindo) { seguindo = _seguindo; }
        
        void postar_tweet(Tweet tweet);
        void seguir(Usuario _usuario);

};
int main(){

    return 0;
}

void  Usuario::postar_tweet(Tweet tweet){


}
void  Usuario::seguir(Usuario _usuario){

}