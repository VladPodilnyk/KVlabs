from controller import Controller, Model

data_base = Model('data.txt')
data_controller = Controller(data_base)
data_controller.run()
