#include "utils.hpp"

std::string normalizeText(std::string_view text) {
    std::string result;
    result.reserve(text.size() * 1.1);
    for (char ch : text) {
        switch (ch) {
            case '\n':
                result.append("\\n");
                break;
            case '"':
                result.append("\\\"");
                break;
            case '\t':
                result.append("\\t");
                break;
            default:
                result.push_back(ch);
        }
    }

    return result;
}

std::string toUpperCase(std::string_view input) {
    std::string result(input);
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string toLowerCase(std::string_view input) {
    std::string result(input);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

const std::string getDate() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M-%S", &tstruct);

    return buf;
}

int64_t getTimeStamp() {
    return static_cast<int64_t>(time(0));
}

const char *get_arg_value(int argc, char **argv, const char *target_arg){
    for(int arg_idx = 0; arg_idx < argc; arg_idx++){
        if(!strcmp(argv[arg_idx], target_arg)) // <arg> <value> 
            return argv[arg_idx+1]==nullptr?"":argv[arg_idx+1];
    }
    return nullptr;
}

void printCmdHelp(){
    std::cout << "Usage:\n \
    --prompt <my_prompt_name> (default: creative)\n \
    --param-profile <profile_name> (default: samantha)\n \
    --chat-template <template_name> (default: None)\n \
    --no-chat-tags Disable chat style actors tags (ex:  'User:' 'Someone:')\n \
    --no-chat-guards (default: true)\n \
    --ip <ip address> (default: 127.0.0.1)\n \
    --port <port> (default: 8080)" << std::endl;
}


void printChatHelp() {
    std::cout << "Conversation manipulation:\n \
    /narrator: Lets the narrator generate a narration.\n \
    /actor / now: Choose who will talk now. If the actor doesn't exist, it will be created. (e.g., /now Einstein)\n \
    /as: Pretend to be an actor and prompt it. (e.g., /as Einstein)\n \
    /talkto: Talk to a specific character. It will switch the current talking actor. (e.g., /talkto Monica)\n \
    /insert / i: Multiline mode insertion. To finish and submit, write \"EOL\" or \"eol\" and then press enter.\n \
    /retry / r: Retry the last completion.\n \
    /edit: Edit the assistant last message to re-submit it. \n \
    /continue: Continue the completion without intervention. (The assistant will continue talking)\n \
    /undolast: Undo only the last completion.\n \
    /undo / u: Undo the last completion and user input.\n\n \
Conversation mode:\n \
    /chat on/off: Turn on/off chat tags.\n\n \
Conversation saving:\n \
    /save (chatname): Save the chat (without extension).\n \
    /load (chatname): Load a previously saved chat.\n\n \
Manage configurations:\n \
    /redraw: Redraw the chat content.\n \
    /reset: Reset the entire chat.\n \
    /quit / q: Exit the program.\n \
    /lprompt: Print the current prompt.\n \
    /lactors: Print current actors.\n \
    /lparams: Print the current parameters.\n \
    /rparams: Reload the current parameter profile.\n \
    /rtemplate: Reload the current template profile.\n \
    /sparam (parameter profile name): Load and set param profile in runtime from param.json.\n \
    /stemplate (template name): Load and set prompt template in runtime from template.json.\n \
    /ssystem (new system prompt): Set new system prompt (from begin).\n \
    /sprompt (prompt name): Load and set custom prompt in runtime from prompt.json.\n\n" << std::endl;

}
