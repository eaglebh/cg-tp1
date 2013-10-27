#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "../Graphical.h"
#include "../Scene.h"

TEST(GetPosition, NoData) {
    Graphical graphical1(1);
    Position p1;
    p1.setX(1.0f)->setY(1.0f)->setZ(1.0f);
    graphical1.setRelativePosition(p1);

    Graphical graphical1_1(11, &graphical1);
    Position p1_1;
    p1_1.setX(0.2f)->setY(0.3f)->setZ(0.4f);
    graphical1_1.setRelativePosition(p1_1);

    EXPECT_EQ(1, graphical1.getPosition().getX());
    EXPECT_EQ(1, graphical1.getPosition().getY());
    EXPECT_EQ(1, graphical1.getPosition().getZ());

    EXPECT_EQ(1.2f, graphical1_1.getPosition().getX());
    EXPECT_EQ(1.3f, graphical1_1.getPosition().getY());
    EXPECT_EQ(1.4f, graphical1_1.getPosition().getZ());
}

TEST(GetPosition, Translate) {
    Graphical graphical1(1);
    Position p1;
    p1.setX(1.0f)->setY(1.0f)->setZ(1.0f);
    graphical1.setRelativePosition(p1);

    EXPECT_EQ(1, graphical1.getPosition().getX());
    EXPECT_EQ(1, graphical1.getPosition().getY());
    EXPECT_EQ(1, graphical1.getPosition().getZ());

    Position p1_1;
    p1_1.setX(0.2f)->setY(0.3f)->setZ(0.4f);
    graphical1.translateInc(p1_1);

    EXPECT_EQ(1.2f, graphical1.getPosition().getX());
    EXPECT_EQ(1.3f, graphical1.getPosition().getY());
    EXPECT_EQ(1.4f, graphical1.getPosition().getZ());

    Position p2;
    p2.setX(0.7f)->setY(0.0f)->setZ(0.0f);
    graphical1.translate(p2);

    EXPECT_EQ(0.7f, graphical1.getPosition().getX());
    EXPECT_EQ(0, graphical1.getPosition().getY());
    EXPECT_EQ(0, graphical1.getPosition().getZ());
}

TEST(Scene, Objects) {
    Scene scene;
    Graphical graphical0(0);
    Position p0;
    p0.setX(-0.5f)->setY(0.0f)->setZ(0.0f);
    graphical0.setRelativePosition(p0);
    Graphical graphical1(1);
    Position p1;
    p1.setX(0.0f)->setY(0.0f)->setZ(0.0f);
    graphical1.setRelativePosition(p1);
    Graphical graphical1_1(11, &graphical1);
    Position p1_1;
    p1_1.setX(0.2f)->setY(0.0f)->setZ(0.0f);
    graphical1_1.setRelativePosition(p1_1);
    Graphical graphical2(2);
    Position p2;
    p2.setX(0.7f)->setY(0.0f)->setZ(0.0f);
    graphical2.setRelativePosition(p2);

    Graphical graphical00(0);
    graphical00.setRelativePosition(p2);

    scene.addObject(graphical0);
    scene.addObject(graphical1);
    scene.addObject(graphical1_1);
    scene.addObject(graphical2);
    scene.addObject(graphical0);

    EXPECT_EQ(4, scene.getObjectCount());
}
