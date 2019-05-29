#include "commandscreen.h"

#include <QVBoxLayout>

CommandScreen::CommandScreen()
{

}

CommandScreen::CommandScreen(const std::vector<QString>& commands, ServerConnection * conn, QWidget *parent) :
    Screen(parent), connection(conn)
{
    commands_layout = new QVBoxLayout( this );

    for( const auto& command : commands )
    {
        auto cmd_object = new Command();
        cmd_object->fromQString(command);
        auto button = createPushButton(command, [cmd_object](){
           cmd_object->launch();
        });
        connect(cmd_object, &Command::sendData, this, [this](QString data) {
           this->connection->sendSimpleMessage(data);
        });
        commands_list.push_back(button);
        commands_layout->addWidget(button);
    }

    auto backButton = createPushButton("Back to menu", [this]() {
       emit backToMenu();
    });
    commands_layout->addWidget(backButton);

    main_layout->addLayout(commands_layout);
}


