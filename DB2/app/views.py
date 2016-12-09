from django.shortcuts import render
from django.contrib import messages
from django.http import HttpResponse, HttpResponseRedirect
from .data_base import Order, Product, Stock, Client
from .forms import OrderForm, NewRecordForm

order = Order()
stock = Stock()
product = Product()
client = Client()

#order.load('orders.csv')
#stock.load('stock.csv')
#product.load('products.csv')
#lient.load('clients.csv')


def index(request):
    return HttpResponse("SuperDelivery: Order List")


def order_list(request):
    return render(request, "order_list.html", {"orders": order.fetch_all()})


def edit(request, order_id):

    if request.method == 'POST':
        if 'delete_btn' in request.POST:
            order.delete_by_id(order_id)
            messages.add_message(request, messages.SUCCESS, 'Order was successfully deleted')
            return HttpResponseRedirect('')

        order_form = OrderForm(request.POST)

        if order_form.is_valid():
            data = {"product_id": request.POST["product_id"], "client_id": request.POST["client_id"],
                    "data_time": request.POST["data_time"], "amount": request.POST["amount"]}

            order.update(order_id, data)
            messages.add_message(request, messages.SUCCESS, 'Doctor object updated successfully')
            return HttpResponseRedirect('/')

    record = order.select_by_id(order_id)[0]
    form = OrderForm(initial=record)
    return render(request, "edit.html", {"order_form": form})


def make_new_order(request):
    new_record_form = NewRecordForm(request.POST)
    if request.method == 'POST':
        if new_record_form.is_valid():
            data = {"product_id": request.POST["product_id"], "client_id": request.POST["client_id"],
                    "data_time": request.POST["data_time"], "amount": request.POST["amount"]}
            order.insert(data)
            return HttpResponseRedirect('/')

    form = NewRecordForm()
    return render(request, "new.html", {"new_rec": form})
