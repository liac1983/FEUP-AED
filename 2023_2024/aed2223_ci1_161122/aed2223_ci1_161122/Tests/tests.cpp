#include <gtest/gtest.h>
#include "UverEats.h"

using testing::Eq;

// Ordenar clientes, decrescente numOrders, em caso de igualdade alfabetico por name
TEST(aed2223_ci1, alinea_a) {
    UverEats u;

    u.sortClients();
    vector<Client> c = u.getClients();

    // teste em vazio
    EXPECT_EQ(0, c.size());
    c.clear();

    // teste numOrders decrescente
    u.addClient(Client("c1", 10));
    u.addClient(Client ("c2", 8));
    u.addClient(Client ("c3", 15));
    u.addClient(Client ("c4", 2));

    u.sortClients();
    c = u.getClients();
    EXPECT_EQ(4, c.size());
    if (c.size() == 4)
        for (int i=0;i<c.size()-1;i++)
            EXPECT_GE(c[i].getSeniority(), c[i + 1].getSeniority());

    UverEats u2;
    // teste name crescente
    u2.addClient(Client("c1", 10));
    u2.addClient(Client ("c2", 8));
    u2.addClient(Client ("c3", 15));
    u2.addClient(Client ("c4", 2));
    u2.addClient(Client ("a4", 2));
    u2.addClient(Client ("a1", 10));

    u2.sortClients();
    c = u2.getClients();
    EXPECT_EQ(6, c.size());
    if (c.size() == 6)
        for (int i=0;i<c.size()-1;i++) {
            EXPECT_GE(c[i].getSeniority(), c[i + 1].getSeniority());
            if (c[i].getSeniority() == c[i + 1].getSeniority())
                EXPECT_LT(c[i].getName(),c[i+1].getName());
        }
}


// Média do rating dos restaurantes com mais do que n pedidos
TEST(aed2223_ci1, alinea_b) {
    UverEats u1;

    Restaurant r11 = Restaurant("r11", 9.0);
    r11.insertOrder(new Order("1", "c1"));
    r11.insertOrder(new Order("2", "c2"));
    r11.insertOrder(new Order("3", "c3"));
    r11.insertOrder(new Order("4", "c4"));
    r11.insertOrder(new Order("5", "c5"));
    u1.addRestaurant(r11);

    Restaurant r12 = Restaurant("r12", 10.0);
    r12.insertOrder(new Order("1", "c1"));
    r12.insertOrder(new Order("2", "c2"));
    r12.insertOrder(new Order("3", "c3"));
    u1.addRestaurant(r12);

    Restaurant r13 = Restaurant("r13", 5.0);
    r13.insertOrder(new Order("1", "c1"));
    r13.insertOrder(new Order("2", "c2"));
    u1.addRestaurant(r13);

    EXPECT_NEAR(9.5, u1.averageRestaurantRating(2),0.01);
    EXPECT_NEAR(9.0, u1.averageRestaurantRating(3),0.01);

    //=========================================================================

    UverEats u2;
    Restaurant r21 = Restaurant("r21", 9.0);
    r21.insertOrder(new Order("1", "c1"));
    Restaurant r22 = Restaurant("r22", 5.0);
    r22.insertOrder(new Order("3", "c3"));
    Restaurant r23 = Restaurant("r23", 7.5);

    EXPECT_NEAR(0.0, u2.averageRestaurantRating(2),0.01);

    //=========================================================================

    UverEats u3;
    Restaurant r31 = Restaurant("r31", 9.0);
    r31.insertOrder(new Order("1", "c1"));
    r31.insertOrder(new Order("2", "c2"));
    r31.insertOrder(new Order("3", "c3"));
    r31.insertOrder(new Order("4", "c4"));
    r31.insertOrder(new Order("5", "c5"));
    u3.addRestaurant(r31);

    Restaurant r32 = Restaurant("r32", 10.0);
    r32.insertOrder(new Order("1", "c1"));
    r32.insertOrder(new Order("2", "c2"));
    r32.insertOrder(new Order("3", "c3"));
    u3.addRestaurant(r32);

    Restaurant r33 = Restaurant("r33", 5.0);
    r33.insertOrder(new Order("1", "c1"));
    r33.insertOrder(new Order("2", "c2"));
    u3.addRestaurant(r33);

    Restaurant r34 = Restaurant("r34", 5.0);
    r34.insertOrder(new Order("1", "c1"));
    r34.insertOrder(new Order("2", "c2"));
    r34.insertOrder(new Order("3", "c3"));
    u3.addRestaurant(r34);

    Restaurant r35 = Restaurant("r35", 9.0);
    r35.insertOrder(new Order("1", "c1"));
    r35.insertOrder(new Order("2", "c2"));
    u3.addRestaurant(r35);

    Restaurant r36 = Restaurant("r36", 5.5);
    r36.insertOrder(new Order("1", "c1"));
    r36.insertOrder(new Order("2", "c2"));
    u3.addRestaurant(r36);

    EXPECT_NEAR(8.0, u3.averageRestaurantRating(2),0.01);
    EXPECT_NEAR(9.0, u3.averageRestaurantRating(3),0.01);
    EXPECT_NEAR(9.0, u3.averageRestaurantRating(4),0.01);
    EXPECT_NEAR(7.25, u3.averageRestaurantRating(1),0.01);
}


// desistencia de cliente, remocao de um pedido da fila de pedidos
TEST(aed2223_ci1, alinea_c) {
    Restaurant r1;

    r1.insertOrder(new Order("1", "c1"));
    queue<Order*> q1 = r1.getOrders();
    EXPECT_EQ(1, q1.size());

    // Remove única encomenda
    r1.removeOrder("c1", "1");
    q1 = r1.getOrders();
    EXPECT_EQ(0, q1.size());

    //=========================================================================
    // Insere 5 encomendas, remove uma
    Restaurant r2;
    r2.insertOrder(new Order("1", "c1"));
    r2.insertOrder(new Order("2", "c2"));
    r2.insertOrder(new Order("3", "c3"));
    r2.insertOrder(new Order("4", "c4"));
    r2.insertOrder(new Order("5", "c5"));
    r2.removeOrder("c4", "4");

    queue<Order*> q2 = r2.getOrders();
    EXPECT_EQ(4, q2.size());
    if (q2.size() == 4) {
        EXPECT_EQ("c1", q2.front()->getClient());
        q2.pop();
        EXPECT_EQ("c2", q2.front()->getClient());
        q2.pop();
        EXPECT_EQ("c3", q2.front()->getClient());
        q2.pop();
        EXPECT_EQ("c5", q2.front()->getClient());
        q2.pop();
        EXPECT_EQ(0, q2.size());
    }

    //=========================================================================
    // Insere 4 encomendas, remove ultima
    Restaurant r3;
    r3.insertOrder(new Order("1", "c1"));
    r3.insertOrder(new Order("2", "c2"));
    r3.insertOrder(new Order("3", "c3"));
    r3.insertOrder(new Order("4", "c4"));
    r3.removeOrder("c4", "4");


    queue<Order*> q3 = r3.getOrders();
    EXPECT_EQ(3, q3.size());
    if (q3.size() == 3) {
        EXPECT_EQ("c1", q3.front()->getClient());
        q3.pop();
        EXPECT_EQ("c2", q3.front()->getClient());
        q3.pop();
        EXPECT_EQ("c3", q3.front()->getClient());
        q3.pop();
        EXPECT_EQ(0, q3.size());
    }

}


// remove restaurantes da lista com rating inferior a X
TEST(aed2223_ci1, alinea_d) {
    UverEats u1;

    // remove único restaurante
    u1.addRestaurant(Restaurant("r1", 9.0));
    list<Restaurant> l1 = u1.getRestaurants();
    u1.removeRestaurants(10.0);
    l1 = u1.getRestaurants();
    EXPECT_EQ(0, l1.size());
    l1.clear();

    //=========================================================================
    // remove um restaurante
    UverEats u2;
    u2.addRestaurant(Restaurant("r1", 9.0));
    u2.addRestaurant(Restaurant("r2", 10.0));
    u2.addRestaurant(Restaurant("r3", 5.0));
    u2.addRestaurant(Restaurant("r4", 8.0));
    list<Restaurant> l2 = u2.getRestaurants();
    u2.removeRestaurants(6.0);
    l2 = u2.getRestaurants();

    EXPECT_EQ(3, l2.size());
    if (l2.size() == 3){
        EXPECT_EQ("r1", l2.front().getName());
        l2.pop_front();
        EXPECT_EQ("r2", l2.front().getName());
        l2.pop_front();
        EXPECT_EQ("r4", l2.front().getName());
        l2.pop_front();
        EXPECT_EQ(0, l2.size());
        l2.clear();
    }

    //=========================================================================
    // remove dois restaurantes não consecutivos
    UverEats u3;
    u3.addRestaurant(Restaurant("r1", 9.0));
    u3.addRestaurant(Restaurant("r2", 10.0));
    u3.addRestaurant(Restaurant("r3", 5.0));
    u3.addRestaurant(Restaurant("r4", 8.0));
    u3.addRestaurant(Restaurant("r5", 6.0));
    list<Restaurant> l3 = u3.getRestaurants();
    EXPECT_EQ(5, l3.size());
    u3.removeRestaurants(7.0);
    l3 = u3.getRestaurants();
    EXPECT_EQ(3, l3.size());
    if (l3.size() == 3){
        EXPECT_EQ("r1", l3.front().getName());
        l3.pop_front();
        EXPECT_EQ("r2", l3.front().getName());
        l3.pop_front();
        EXPECT_EQ("r4", l3.front().getName());
        l3.pop_front();
        EXPECT_EQ(0, l3.size());
        l3.clear();
    }

    //=========================================================================
    // remove dois restaurantes consecutivos
    UverEats u4;
    u4.addRestaurant(Restaurant("r1", 9.0));
    u4.addRestaurant(Restaurant("r2", 5.0));
    u4.addRestaurant(Restaurant("r3", 5.0));
    u4.addRestaurant(Restaurant("r4", 8.0));
    u4.addRestaurant(Restaurant("r5", 6.0));
    list<Restaurant> l4 = u4.getRestaurants();
    EXPECT_EQ(5, l4.size());
    u4.removeRestaurants(6.0);
    l4 = u4.getRestaurants();
    EXPECT_EQ(3, l4.size());
    if (l4.size() == 3){
        EXPECT_EQ("r1", l4.front().getName());
        l4.pop_front();
        EXPECT_EQ("r4", l4.front().getName());
        l4.pop_front();
        EXPECT_EQ("r5", l4.front().getName());
        l4.pop_front();
        EXPECT_EQ(0, l4.size());
        l4.clear();
    }

    //=========================================================================
    // tenta remover inexistente
    UverEats u5;
    u5.addRestaurant(Restaurant("r1", 9.0));
    u5.addRestaurant(Restaurant("r2", 9.0));
    list<Restaurant> l5 = u5.getRestaurants();
    EXPECT_EQ(2, l5.size());
    u5.removeRestaurants(8.0);
    l5 = u5.getRestaurants();
    EXPECT_EQ(2, l5.size());
    l5.clear();

}


// procura encomendas comuns na fila de dois condutores
TEST(aed2223_ci1, alinea_e) {
    Driver d1 =Driver(1, "d1");
    Driver d2 =Driver(2, "d2");

    stack<Order> d1o = d1.getToDeliver();
    stack<Order> d2o = d2.getToDeliver();


    vector<string> cc1 = d1.checkCommonClients(d2);
    d1o = d1.getToDeliver();
    d2o = d2.getToDeliver();
    EXPECT_EQ(0, d1o.size());
    EXPECT_EQ(0, d2o.size());

    EXPECT_EQ(0, cc1.size());

    //=========================================================================
    // Retorna 1 repetido, mas sem testar se mantém as pilhas dos condutores
    Driver d3 = Driver(3, "d3");
    d3.insertOrder(Order("o1", "c1"));
    d3.insertOrder(Order("o2", "c2"));

    Driver d4 = Driver(4, "d4");
    d4.insertOrder(Order("o3", "c3"));
    d4.insertOrder(Order("o4", "c1"));

    vector<string> cc2 = d3.checkCommonClients(d4);
    stack<Order> d3o = d3.getToDeliver();
    stack<Order> d4o = d4.getToDeliver();
    EXPECT_EQ(1, cc2.size());
    if (cc2.size() == 1){
        EXPECT_EQ("c1", cc2[0]);
    }

    //=========================================================================
    // Retorna 3 e testa se mantém as pilhas dos condutores
    Driver d5 = Driver(5, "d5");
    d5.insertOrder(Order("o1", "c1"));
    d5.insertOrder(Order("o2", "c2"));
    d5.insertOrder(Order("o5", "c5"));
    d5.insertOrder(Order("o7", "c7"));
    d5.insertOrder(Order("o9", "c9"));

    Driver d6 = Driver(6, "d6");
    d6.insertOrder(Order("o3", "c3"));
    d6.insertOrder(Order("o8", "c1"));
    d6.insertOrder(Order("o4", "c4"));
    d6.insertOrder(Order("o10", "c2"));
    d6.insertOrder(Order("o6", "c5"));

    stack<Order> d5o = d5.getToDeliver();
    stack<Order> d6o = d6.getToDeliver();
    EXPECT_EQ(5, d5o.size());
    EXPECT_EQ(5, d6o.size());

    vector<string> cc3 = d5.checkCommonClients(d6);
    d5o = d5.getToDeliver();
    d6o = d6.getToDeliver();
    EXPECT_EQ(5, d5o.size());
    EXPECT_EQ(5, d6o.size());
    EXPECT_EQ(3, cc3.size());
    if (cc3.size() == 3){
        EXPECT_EQ(true, std::find(cc3.begin(), cc3.end(), "c5") != cc3.end());
        EXPECT_EQ(true, std::find(cc3.begin(), cc3.end(), "c2") != cc3.end());
        EXPECT_EQ(true, std::find(cc3.begin(), cc3.end(), "c1") != cc3.end());
    }

    // Testa se nao existem clientes em comum
    Driver d9 = Driver(9, "d9");
    d9.insertOrder(Order("o1", "c1"));
    d9.insertOrder(Order("o2", "c2"));

    Driver d10 = Driver(10, "d10");
    d10.insertOrder(Order("o3", "c3"));

    stack<Order> d9o = d9.getToDeliver();
    stack<Order> d10o = d10.getToDeliver();

    vector<string> u4cc1 = d9.checkCommonClients(d10);
    d9o = d9.getToDeliver();
    d10o = d10.getToDeliver();
    EXPECT_EQ(0, u4cc1.size());
    EXPECT_EQ(2, d9.getToDeliver().size());
    EXPECT_EQ(1, d10.getToDeliver().size());
}


// procura lista de condutores com menos de n pedidos, retorna em vector ordenado descrescente numOrders, em caso de igualdade alfabético driverName
TEST(aed2223_ci1, alinea_f) {
    UverEats u1;

    Driver u1d1 = Driver(1, "a");
    u1d1.insertOrder(Order("d1o1", "c1"));
    u1d1.insertOrder(Order("d1o2", "c2"));
    u1.addDriver(u1d1);

    Driver u1d2 = Driver(2, "b");
    u1d2.insertOrder(Order("d2o1", "c1"));
    u1d2.insertOrder(Order("d2o2", "c2"));
    u1d2.insertOrder(Order("d2o3", "c3"));
    u1.addDriver(u1d2);

    Driver u1d3 = Driver(3, "c");
    u1d3.insertOrder(Order("d3o1", "c1"));
    u1.addDriver(u1d3);

    set<Driver> u1d = u1.getDrivers();

    // testa construcao set
    EXPECT_EQ(3, u1d.size());
    if (u1d.size() == 3) {
        Driver dx = *u1d.begin();
        EXPECT_EQ(2, dx.getIdDriver());
    }

    // vector vazio
    vector<Driver> u1dv1 = u1.getDriversWithOrders(1);
    EXPECT_EQ(0, u1dv1.size());


    // menos de 2 pedidos
    u1dv1 = u1.getDriversWithOrders(2);
    EXPECT_EQ(1, u1dv1.size());
    if (u1dv1.size() == 1) {
        EXPECT_EQ(1, u1dv1[0].getToDeliver().size());
        EXPECT_EQ(3, u1dv1[0].getIdDriver());
        EXPECT_EQ("c", u1dv1[0].getNameDriver());
    }

    // menos de 3 pedidos
    u1dv1 = u1.getDriversWithOrders(3);
    EXPECT_EQ(2, u1dv1.size());
    if (u1dv1.size() == 2) {
        EXPECT_EQ(2, u1dv1[0].getToDeliver().size());
        EXPECT_EQ(1, u1dv1[0].getIdDriver());
        EXPECT_EQ("a", u1dv1[0].getNameDriver());

        EXPECT_EQ(1, u1dv1[1].getToDeliver().size());
        EXPECT_EQ(3, u1dv1[1].getIdDriver());
        EXPECT_EQ("c", u1dv1[1].getNameDriver());
    }


    //=========================================================================
    // com número de pedidos iguais
    UverEats u2;

    Driver u2d1 = Driver(1, "a");
    u2d1.insertOrder(Order("d1o1", "c1"));
    u2d1.insertOrder(Order("d1o2", "c2"));
    u2d1.insertOrder(Order("d1o3", "c1"));
    u2.addDriver(u2d1);

    Driver u2d2 = Driver(2, "f");
    u2d2.insertOrder(Order("d2o1", "c1"));
    u2d2.insertOrder(Order("d2o2", "c2"));
    u2d2.insertOrder(Order("d2o3", "c3"));
    u2.addDriver(u2d2);

    Driver u2d3 = Driver(3, "c");
    u2.addDriver(u2d3);

    Driver u2d4 = Driver(4, "b");
    u2d4.insertOrder(Order("d4o1", "c1"));
    u2d4.insertOrder(Order("d4o2", "c2"));
    u2d4.insertOrder(Order("d4o3", "c3"));
    u2d4.insertOrder(Order("d4o4", "c3"));
    u2d4.insertOrder(Order("d4o5", "c2"));
    u2d4.insertOrder(Order("d4o6", "c1"));
    u2.addDriver(u2d4);

    Driver u2d5 = Driver(5, "a");
    u2d5.insertOrder(Order("d5o1", "c1"));
    u2.addDriver(u2d5);

    Driver u2d6 = Driver(6, "b");
    u2d6.insertOrder(Order("d6o1", "c1"));
    u2d6.insertOrder(Order("d6o2", "c2"));
    u2d6.insertOrder(Order("d6o3", "c2"));
    u2d6.insertOrder(Order("d6o4", "c3"));
    u2.addDriver(u2d6);

    Driver u2d7 = Driver(7, "b");
    u2d7.insertOrder(Order("d7o1", "c1"));
    u2d7.insertOrder(Order("d7o2", "c2"));
    u2d7.insertOrder(Order("d7o3", "c3"));
    u2.addDriver(u2d7);

    vector<Driver> u2dv1 = u2.getDriversWithOrders(4);
    EXPECT_EQ(5, u2dv1.size());

    if (u2dv1.size() == 5) {
        EXPECT_EQ(3, u2dv1[0].getToDeliver().size());
        EXPECT_EQ(1, u2dv1[0].getIdDriver());
        EXPECT_EQ("a", u2dv1[0].getNameDriver());

        EXPECT_EQ(3, u2dv1[1].getToDeliver().size());
        EXPECT_EQ(2, u2dv1[1].getIdDriver());
        EXPECT_EQ("f", u2dv1[1].getNameDriver());

        EXPECT_EQ(3, u2dv1[2].getToDeliver().size());
        EXPECT_EQ(7, u2dv1[2].getIdDriver());
        EXPECT_EQ("b", u2dv1[2].getNameDriver());

        EXPECT_EQ(1, u2dv1[3].getToDeliver().size());
        EXPECT_EQ(5, u2dv1[3].getIdDriver());
        EXPECT_EQ("a", u2dv1[3].getNameDriver());

        EXPECT_EQ(0, u2dv1[4].getToDeliver().size());
        EXPECT_EQ(3, u2dv1[4].getIdDriver());
        EXPECT_EQ("c", u2dv1[4].getNameDriver());
    }

}


TEST(aed2223_ci1, alinea_g) {
    UverEats u1;
    u1.addRestaurant(Restaurant("u1r1"));
    u1.addRestaurant(Restaurant("u1r2"));
    u1.addRestaurant(Restaurant("u1r3"));
    u1.addRestaurant(Restaurant("u1r4"));

    Restaurant u1rx = Restaurant("u1rx");
    u1.addRestaurant(u1rx);
    EXPECT_EQ(0, u1rx.getOrders().size());

    u1.createRestaurantBranch("u1rx", "u1rnew");
    list<Restaurant> rests = u1.getRestaurants();
    list<Restaurant>::iterator u1it= find_if(rests.begin(), rests.end(),[](Restaurant const &o) {
        return (o.getName()=="u1rx"); });
    EXPECT_EQ(false, u1it==rests.end());
    if (u1it!=rests.end()) {
        EXPECT_EQ(0, u1it->getOrders().size());
    }

    EXPECT_EQ(false, u1.getRestaurants().empty());
    if (u1.getRestaurants().empty() == false) {
        EXPECT_EQ("u1rnew", u1.getRestaurants().back().getName());
        EXPECT_EQ(0, u1.getRestaurants().back().getOrders().size());
    }


    //=========================================================================

    UverEats u2;
    u2.addRestaurant(Restaurant("u2r1"));
    u2.addRestaurant(Restaurant("u2r2"));
    u2.addRestaurant(Restaurant("u2r3"));
    u2.addRestaurant(Restaurant("u2r4"));

    Restaurant u2rx = Restaurant("u2rx");
    u2rx.insertOrder(new Order("u2rx1", "rxc1"));
    u2rx.insertOrder(new Order("u2rx2", "rxc2"));
    u2.addRestaurant(u2rx);

    EXPECT_EQ(2, u2rx.getOrders().size());

    u2.createRestaurantBranch("u2rx", "u2rnew");
    rests = u2.getRestaurants();
    list<Restaurant>::iterator u2it= find_if(rests.begin(), rests.end(),[](Restaurant const &o) {
        return (o.getName()=="u2rx"); });
    EXPECT_EQ(false, u2it==rests.end());

    if (u2it!=rests.end()) {
        queue<Order *> u2rxo = u2it->getOrders();
        EXPECT_EQ(1, u2rxo.size());
        if (u2rxo.size() == 1) {
            EXPECT_EQ("rxc1", u2rxo.front()->getClient());
            EXPECT_EQ("u2rx1", u2rxo.front()->getOrderNumber());
            u2rxo.pop();
            EXPECT_EQ(true, u2rxo.empty());
        }
    }

    EXPECT_EQ(false, u2.getRestaurants().empty());
    if (u2.getRestaurants().empty() == false) {
        Restaurant u2rnew = u2.getRestaurants().back();
        EXPECT_EQ("u2rnew", u2rnew.getName());
        queue<Order*> u2rnewo = u2rnew.getOrders();
        EXPECT_EQ(1, u2rnewo.size());
        if (u2rnewo.size() == 1) {
            EXPECT_EQ("rxc2", u2rnew.getOrders().front()->getClient());
            EXPECT_EQ("u2rx2", u2rnew.getOrders().front()->getOrderNumber());
            u2rnewo.pop();
            EXPECT_EQ(true, u2rnewo.empty());
        }
    }


    //=========================================================================

    UverEats u3;
    u3.addRestaurant(Restaurant("u3r1"));
    u3.addRestaurant(Restaurant("u3r2"));
    u3.addRestaurant(Restaurant("u3r3"));
    u3.addRestaurant(Restaurant("u3r4"));

    Restaurant u3rx = Restaurant("u3rx");
    u3rx.insertOrder(new Order("u3rx1", "rxc1"));
    u3rx.insertOrder(new Order("u3rx2", "rxc2"));
    u3rx.insertOrder(new Order("u3rx3", "rxc3"));
    u3rx.insertOrder(new Order("u3rx4", "rxc4"));
    u3rx.insertOrder(new Order("u3rx5", "rxc5"));
    u3.addRestaurant(u3rx);

    EXPECT_EQ(5, u3rx.getOrders().size());

    u3.createRestaurantBranch("u3rx", "u3rnew");
    rests = u3.getRestaurants();
    list<Restaurant>::iterator u3it= find_if(rests.begin(), rests.end(),[](Restaurant const &o) {
        return (o.getName()=="u3rx"); });
    EXPECT_EQ(false, u3it==rests.end());

    if (u3it!=rests.end()) {
        queue<Order*> u3rxo = u3it->getOrders();
        EXPECT_EQ(3, u3rxo.size());
        if (u3rxo.size() == 3) {
            EXPECT_EQ("rxc1", u3rxo.front()->getClient());
            EXPECT_EQ("u3rx1", u3rxo.front()->getOrderNumber());
            u3rxo.pop();
            EXPECT_EQ("rxc3", u3rxo.front()->getClient());
            EXPECT_EQ("u3rx3", u3rxo.front()->getOrderNumber());
            u3rxo.pop();
            EXPECT_EQ("rxc5", u3rxo.front()->getClient());
            EXPECT_EQ("u3rx5", u3rxo.front()->getOrderNumber());
            u3rxo.pop();
            EXPECT_EQ(true, u3rxo.empty());
        }
    }


    EXPECT_EQ(false, u3.getRestaurants().empty());
    if (u3.getRestaurants().empty() == false) {
        Restaurant u3rnew = u3.getRestaurants().back();
        EXPECT_EQ("u3rnew", u3rnew.getName());
        queue<Order*> u3rnewo = u3rnew.getOrders();
        EXPECT_EQ(2, u3rnewo.size());
        if (u3rnewo.size() == 2) {
            EXPECT_EQ("rxc2", u3rnewo.front()->getClient());
            EXPECT_EQ("u3rx2", u3rnewo.front()->getOrderNumber());
            u3rnewo.pop();
            EXPECT_EQ("rxc4", u3rnewo.front()->getClient());
            EXPECT_EQ("u3rx4", u3rnewo.front()->getOrderNumber());
            u3rnewo.pop();
            EXPECT_EQ(true, u3rnewo.empty());
        }
    }


    //=========================================================================

    UverEats u4;
    u4.addRestaurant(Restaurant("u4r1"));
    u4.addRestaurant(Restaurant("u4r2"));
    u4.addRestaurant(Restaurant("u4r3"));
    u4.addRestaurant(Restaurant("u4r4"));

    Restaurant u4rx = Restaurant("u4rx");
    u4rx.insertOrder(new Order("u4rx1", "rxc1"));
    u4rx.insertOrder(new Order("u4rx2", "rxc2"));
    u4rx.insertOrder(new Order("u4rx3", "rxc3"));
    u4rx.insertOrder(new Order("u4rx4", "rxc4"));
    u4rx.insertOrder(new Order("u4rx5", "rxc5"));
    u4rx.insertOrder(new Order("u4rx6", "rxc6"));
    u4.addRestaurant(u4rx);

    EXPECT_EQ(6, u4rx.getOrders().size());

    u4.createRestaurantBranch("u4rx", "u4rnew");
    rests = u4.getRestaurants();
    list<Restaurant>::iterator u4it= find_if(rests.begin(), rests.end(),[](Restaurant const &o) {
        return (o.getName()=="u4rx"); });
    EXPECT_EQ(false, u4it==rests.end());

    if (u4it!=rests.end()) {
        queue<Order*> u4rxo = u4it->getOrders();
        EXPECT_EQ(3, u4rxo.size());
        if (u4rxo.size() == 3) {
            EXPECT_EQ("rxc1", u4rxo.front()->getClient());
            EXPECT_EQ("u4rx1", u4rxo.front()->getOrderNumber());
            u4rxo.pop();
            EXPECT_EQ("rxc3", u4rxo.front()->getClient());
            EXPECT_EQ("u4rx3", u4rxo.front()->getOrderNumber());
            u4rxo.pop();
            EXPECT_EQ("rxc5", u4rxo.front()->getClient());
            EXPECT_EQ("u4rx5", u4rxo.front()->getOrderNumber());
            u4rxo.pop();
            EXPECT_EQ(true, u4rxo.empty());
        }
    }


    EXPECT_EQ(false, u4.getRestaurants().empty());
    if (u4.getRestaurants().empty() == false) {
        Restaurant u4rnew = u4.getRestaurants().back();
        EXPECT_EQ("u4rnew", u4rnew.getName());
        queue<Order*> u4rnewo = u4rnew.getOrders();
        EXPECT_EQ(3, u4rnewo.size());
        if (u4rnewo.size() == 3) {
            EXPECT_EQ("rxc2", u4rnewo.front()->getClient());
            EXPECT_EQ("u4rx2", u4rnewo.front()->getOrderNumber());
            u4rnewo.pop();
            EXPECT_EQ("rxc4", u4rnewo.front()->getClient());
            EXPECT_EQ("u4rx4", u4rnewo.front()->getOrderNumber());
            u4rnewo.pop();
            EXPECT_EQ("rxc6", u4rnewo.front()->getClient());
            EXPECT_EQ("u4rx6", u4rnewo.front()->getOrderNumber());
            u4rnewo.pop();
            EXPECT_EQ(true, u4rnewo.empty());
        }
    }

}