#include "../static.headers/lib.h"

int menu() {
    int min = 0, max = 4;
    int i = 164;
    aes::print_text("\n Administrador de contrasenas ");
    aes::print_text("  0. Salir del programa");
    aes::print_text("  1. Agrega un nuevo servicio");
    aes::print_text("  2. Busca un servicio");
    aes::print_text("  3. Elimina un servicio");
    aes::print_text("  4. Modifica un servicio");

    std::string option = aes::get_text("Ingresa una opcion: ");

    if(aes::sanitize_stringint(option) != "") {
        int option_int = std::stoi(option);
        if(aes::between(option_int, min, max, 3)) return option_int;
    }
    else {
        aes::print_text("\n  La opcion es invalida");
        system("pause");
        system("clear");
        system("cls");
    }
    return menu();
}

std::string check_random(std::string text) {
    int pos = text.find(' ');
    if(pos != std::string::npos) {
        std::string random = aes::string_tolower(text.substr(0, pos));
        if(random == "random") {
            auto length = aes::sanitize_stringint(text.substr(pos + 1, text.size()));
            if(length != "") {
                return aes::random_string(std::stoi(length));
            }
            else return aes::random_string();
        }
    }
    return text;
}

void start() {
    aes::create_directory("data");
    if(aes::create_file("data/names.txt")) {
        auto a = aes::TextManager("data/names.txt");
        a.write_line("index=0");
    }
    aes::create_file("data/data.txt");
}

std::string get_service() {
    return aes::get_text("\n  Ingresa el nombre del servicio: ");
}

void add() {
    std::string service_name = aes::no_whitespace(aes::string_toupper(get_service()));
    if(service_name == "CANCEL") return;
    auto names = aes::TextManager("data/names.txt");
    auto data = aes::TextManager("data/data.txt");

    if(names.get_variable(service_name) != "") {
        aes::print_text("\n   El servicio ya existe");
        return;
    }
    else {
        aes::print_text(" 'random (largo) | random 4 -> vS3& '");

        auto user = aes::get_text("\n  Ingresa el usuario            : ");
        auto password = aes::get_text("\n  Ingresa la contrasena         : ");
        auto extra = aes::get_text("\n  Ingresa la informacion extra  : ");

        if(user == "CANCEL" || password == "CANCEL" || extra == "CANCEL") return;

        if(user == "") user = "Sin informacion";
        if(password == "") password = "Sin informacion";
        if(extra == "") extra = "Sin informacion";

        user = check_random(user);
        password = check_random(password);
        extra = check_random(extra);

        auto encrypt_timer = ProcessTimer("Encrypting the data", true, false);

        auto data_index = aes::encrypt(user) + "-" + aes::encrypt(password) + "-" + aes::encrypt(extra);
        auto index = names.get_variable("index");

        names.write_line(service_name + '=' + index);
        data.write_line(index + '=' + data_index);
        names.set_variable("index", std::to_string(std::stoi(index) + 1));

        aes::print_text("\n   El servicio se agrego en el index [" + index + "]\n\tTiempo de encriptacion [" + std::to_string(encrypt_timer.get_time()) + "]");
    }
}

void search() {
    std::string service_name = aes::no_whitespace(aes::string_toupper(get_service()));
    if(service_name == "CANCEL") return;
    auto names = aes::TextManager("data/names.txt");
    auto data = aes::TextManager("data/data.txt");

    auto search_timer = ProcessTimer("Searching the service", true, false);

    auto index = names.get_variable(service_name);
    if(index == "") {
        aes::print_text("\n   No se encontro el servicio");
        return;
    }
    else {
        auto data_index = data.get_variable(index);
        auto vec = aes::split(data_index, '-');

        aes::print_text("\nEl servicio en el index [" + index + "]\n\tTiempo de busqueda [" + std::to_string(search_timer.get_time()) + "]");

        auto decrypt_timer = ProcessTimer("Decrypting the data", true, false);
        aes::print_text("\nUsuario           :  " + aes::decrypt(vec[0]));
        aes::print_text("Contrasena        :  " + aes::decrypt(vec[1]));
        aes::print_text("Informacion extra :  " + aes::decrypt(vec[2]));
        aes::print_text("\nDesencriptado completado [" + std::to_string(decrypt_timer.get_time()) + "]");
    }
}

void remove() {
    std::string service_name = aes::no_whitespace(aes::string_toupper(get_service()));
    if(service_name == "CANCEL") return;
    auto names = aes::TextManager("data/names.txt");
    auto data = aes::TextManager("data/data.txt");

    auto search_timer = ProcessTimer("Searching the service", true, false);

    auto index = names.get_variable(aes::no_whitespace(service_name));
    if(index == "") {
        aes::print_text("\n   No se encontro el servicio");
        return;
    }
    else {
        auto remove_timer = ProcessTimer("Removing the service", true, false);

        names.remove_variable(service_name);
        data.remove_variable(index);

        aes::print_text("\n   El servicio se elimino en el index [" + index + "]\n\tTiempo de eliminacion [" + std::to_string(remove_timer.get_time()) + "]");
    }
}

void update() {
    std::string service_name = aes::string_toupper(get_service());
    if(service_name == "CANCEL") return;
    auto names = aes::TextManager("data/names.txt");
    auto data = aes::TextManager("data/data.txt");

    auto search_timer = ProcessTimer("Searching the service", true, false);

    auto index = names.get_variable(aes::no_whitespace(service_name));
    if(index == "") {
        aes::print_text("\n   No se encontro el servicio");
        return;
    }
    else {
        std::vector<std::string> data_vec = aes::split(data.get_variable(index), '-');
        std::vector<std::string> data_vec_decrypt = {aes::decrypt(data_vec[0]), aes::decrypt(data_vec[1]), aes::decrypt(data_vec[2])};

        aes::print_text("\n\t 'AUTO' para no cambiar el valor");
        
        aes::print_text("\n Usuario " + data_vec_decrypt[0]);
        auto user = aes::get_text("\t  Ingresa el usuario            : ");
        aes::print_text("\n Contrasena " + data_vec_decrypt[1]);
        auto password = aes::get_text("\t  Ingresa la contrasena         : ");
        aes::print_text("\n Informacion extra " + data_vec_decrypt[2]);
        auto extra = aes::get_text("\t  Ingresa la informacion extra  : ");

        if(user == "CANCEL" || password == "CANCEL" || extra == "CANCEL") return;

        if(user == "") user = "Sin informacion";
        if(password == "") password = "Sin informacion";
        if(extra == "") extra = "Sin informacion";

        auto update_timer = ProcessTimer("Updating the service", true, false);

        if(aes::string_toupper(user) == "AUTO") user = data_vec_decrypt[0];
        if(aes::string_toupper(password) == "AUTO") password = data_vec_decrypt[1];
        if(aes::string_toupper(extra) == "AUTO") extra = data_vec_decrypt[2];

        user = check_random(user);
        password = check_random(password);
        extra = check_random(extra);

        auto data_index = aes::encrypt(user) + "-" + aes::encrypt(password) + "-" + aes::encrypt(extra);
        data.remove_variable(index);
        data.write_line(index + '=' + data_index);

        aes::print_text("\n   El servicio se actualizo en el index [" + index + "]\n\tTiempo de actualizacion [" + std::to_string(update_timer.get_time()) + "]");
    }
}

int main() {
    auto main = ProcessTimer("Proceso principal");

    start();

    bool bucle = true;

    while(bucle) {
        int option = menu();
        switch(option) {
            case 0:
                bucle = false;
                aes::print_text("Gracias por usar el programa");
                break;
            case 1:
                add();
                break;
            case 2:
                search();
                break;
            case 3:
                remove();
                break;
            case 4:
                update();
                break;
            default:
                aes::print_text("\nLa opcion es invalida");
                break;
        }
        aes::break_line();
        system("pause");
        system("clear");
        system("cls");
    }

    return 0;
}