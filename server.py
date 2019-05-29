#!/usr/bin/python3
# -*- encoding: utf-8 -*-

import time
import subprocess
import pyautogui
import json
import socketserver


LISTENING_ADDRESS = '0.0.0.0'
SERVER_PORT = 9999
#CUSTOM_COMMANDS_FILE='/home/gepard/Projects/rasp_server/custom_commands.txt'
CUSTOM_COMMANDS_FILE='custom_commands.txt'
custom_commands = {}

class MyTCPHandler(socketserver.BaseRequestHandler):
	def onListCommands(self, args):
		print("List Commands")
		print(str(custom_commands.keys()))
		self.request.sendall(str.encode(str(custom_commands.keys())))

	def onScroll(self, args):
		pyautogui.scroll(int(args[0]))

	def onClick(self, args):
		if( args[0] == "lpm" ):
			pyautogui.click()
		elif( args[0] == "ppm" ):
			pyautogui.click(button="right")
		else:
			print("Wrong click button!")

	def onMove(self, args):
		x = args[0]
		y = args[1]
		pyautogui.moveRel(int(x), int(y))

	def onKeyboard(self, args):
		pyautogui.press(args[0])

	def onPrint(self, args):
		separator = ' '
		pyautogui.typewrite(separator.join(args))

	def onCustomCommand(self, command):
		subprocess.Popen(command.split(' '))


	def handle(self):
		print("Hello world!")
		self.greeting_message = "welcome!"
		self.password = "123"
		self.is_connected = False
		self.available_commands = {
			'click': self.onClick,
			'scroll': self.onScroll,
			'move': self.onMove,
			'keyboard': self.onKeyboard,
			'print': self.onPrint,
			'list_commands': self.onListCommands
		}

		current_msg = ""
		while(True):
			test_data = (self.request.recv(1024).decode("utf-8"))
			if not test_data:
				break
			self.data = test_data.strip()
#			print(str(self.data))
			if(self.data == ""):
				time.sleep(0.5)
				continue
			current_msg += self.data
			commands = current_msg.split('#####')
			print(commands)
			commands_len = len(commands)
			if( current_msg.endswith('#####')):
				current_msg = ""
			else:
				current_msg = commands[-1]
				commands_len -= 1
			print(commands_len)

			for i in range(0, commands_len):
				splitted = commands[i].split(' ')
				command = splitted[0]
				print(splitted)
				args = []
				if( len(splitted) > 1 ):
					args = commands[i].split(' ')[1:]
				if( self.is_connected == False ):
					if( command == self.password ):
						self.request.sendall(str.encode(self.greeting_message))
						self.is_connected = True
					else:
						break
				else:
					if( command in self.available_commands.keys() ):
						self.available_commands[command](args)
					elif( command in custom_commands.keys() ):
						self.onCustomCommand(custom_commands[command])
					else:
						print("Unrecognized command")




with open(CUSTOM_COMMANDS_FILE, 'r') as commands_file:
	custom_commands = json.load(commands_file)

print(str(custom_commands))
print(str(custom_commands.keys()))
socketserver.TCPServer.allow_reuse_address = True
server = socketserver.TCPServer((LISTENING_ADDRESS, SERVER_PORT), MyTCPHandler)

server.serve_forever()
