class View:
    @staticmethod
    def data_base_menu():
        print 'Data base menu\n'
        print 'Choose one of the following items\n'
        print '1) Cinemas menu'
        print '2) Sessions menu'
        print '3) Exit'

    @staticmethod
    def display(lst):
        for element in lst:
            print '\n'.join(map(lambda key: key + ' : ' + element[key]), element.keys())
            print '\n'


    @staticmethod
    def cinemas_menu():
        print 'Cinemas menu\n\n'
        print '1) Add cinema\n \
               2) Delete cinema\n \
               3) Update\n \
               4) Display cinema after specific time\n \
               5) Back\n'

    @staticmethod
    def sessions_menu():
        print 'Sessions menu\n\n'
        print '1) Add session\n \
               2) Delete session\n \
               3) Update\n \
               4) Back\n'

    @staticmethod
    def cinemas_update_menu():
        print 'Cinema update menu\n\n'
        print '1) Name\n \
               2) Street\n \
               3) Back\n'

    @staticmethod
    def sessions_update_menu():
        print 'Session update menu\n\n'
        print '1) Name\n \
               2) Time\n \
               3) Cost\n \
               4) Back\n'

    @staticmethod
    def success_message(message):
        print message

    @staticmethod
    def error_message(message):
        print '[ERROR]: ' + message
