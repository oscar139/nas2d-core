#include "NAS2D/Renderer/Rectangle.h"
#include <gtest/gtest.h>


TEST(Rectangle, CreatePointVector) {
	EXPECT_EQ((NAS2D::Rectangle{0, 0, 1, 1}), NAS2D::Rectangle<int>::Create(NAS2D::Point{0, 0}, NAS2D::Vector{1, 1}));
	EXPECT_EQ((NAS2D::Rectangle{1, 1, 2, 3}), NAS2D::Rectangle<int>::Create(NAS2D::Point{1, 1}, NAS2D::Vector{2, 3}));
}

TEST(Rectangle, CreatePointPoint) {
	EXPECT_EQ((NAS2D::Rectangle{0, 0, 1, 1}), NAS2D::Rectangle<int>::Create(NAS2D::Point{0, 0}, NAS2D::Point{1, 1}));
	EXPECT_EQ((NAS2D::Rectangle{1, 1, 1, 2}), NAS2D::Rectangle<int>::Create(NAS2D::Point{1, 1}, NAS2D::Point{2, 3}));
}

TEST(Rectangle, size) {
	EXPECT_EQ((NAS2D::Vector{0, 0}), (NAS2D::Rectangle{0, 0, 0, 0}.size()));
	EXPECT_EQ((NAS2D::Vector{1, 1}), (NAS2D::Rectangle{0, 0, 1, 1}.size()));
	EXPECT_EQ((NAS2D::Vector{3, 4}), (NAS2D::Rectangle{1, 2, 3, 4}.size()));
}

TEST(Rectangle, startPoint) {
	EXPECT_EQ((NAS2D::Point{0, 0}), (NAS2D::Rectangle{0, 0, 0, 0}.startPoint()));
	EXPECT_EQ((NAS2D::Point{0, 0}), (NAS2D::Rectangle{0, 0, 1, 1}.startPoint()));
	EXPECT_EQ((NAS2D::Point{1, 2}), (NAS2D::Rectangle{1, 2, 3, 4}.startPoint()));
}

TEST(Rectangle, endPoint) {
	EXPECT_EQ((NAS2D::Point{0, 0}), (NAS2D::Rectangle{0, 0, 0, 0}.endPoint()));
	EXPECT_EQ((NAS2D::Point{1, 1}), (NAS2D::Rectangle{0, 0, 1, 1}.endPoint()));
	EXPECT_EQ((NAS2D::Point{4, 6}), (NAS2D::Rectangle{1, 2, 3, 4}.endPoint()));
}

TEST(Rectangle, crossXPoint) {
	EXPECT_EQ((NAS2D::Point{0, 0}), (NAS2D::Rectangle{0, 0, 0, 0}.crossXPoint()));
	EXPECT_EQ((NAS2D::Point{1, 0}), (NAS2D::Rectangle{0, 0, 1, 1}.crossXPoint()));
	EXPECT_EQ((NAS2D::Point{4, 2}), (NAS2D::Rectangle{1, 2, 3, 4}.crossXPoint()));
}

TEST(Rectangle, crossYPoint) {
	EXPECT_EQ((NAS2D::Point{0, 0}), (NAS2D::Rectangle{0, 0, 0, 0}.crossYPoint()));
	EXPECT_EQ((NAS2D::Point{0, 1}), (NAS2D::Rectangle{0, 0, 1, 1}.crossYPoint()));
	EXPECT_EQ((NAS2D::Point{1, 6}), (NAS2D::Rectangle{1, 2, 3, 4}.crossYPoint()));
}

TEST(Rectangle, sizeSet) {
	NAS2D::Rectangle rect{1, 2, 3, 4};
	EXPECT_NO_THROW(rect.size({5, 6}));
	EXPECT_EQ((NAS2D::Rectangle{1, 2, 5, 6}), rect);
}

TEST(Rectangle, startPointSet) {
	NAS2D::Rectangle rect{1, 2, 3, 4};
	EXPECT_NO_THROW(rect.startPoint({5, 6}));
	EXPECT_EQ((NAS2D::Rectangle{5, 6, 3, 4}), rect);
}

TEST(Rectangle, skewBy) {
	EXPECT_EQ((NAS2D::Rectangle{1, 0, 1, 0}), (NAS2D::Rectangle{1, 1, 1, 1}.skewBy(NAS2D::Vector{1, 0})));
	EXPECT_EQ((NAS2D::Rectangle{1, 1, 1, 1}), (NAS2D::Rectangle{1, 1, 1, 1}.skewBy(NAS2D::Vector{1, 1})));
	EXPECT_EQ((NAS2D::Rectangle{2, 3, 2, 3}), (NAS2D::Rectangle{1, 1, 1, 1}.skewBy(NAS2D::Vector{2, 3})));
	EXPECT_EQ((NAS2D::Rectangle{4, 6, 4, 6}), (NAS2D::Rectangle{1, 1, 1, 1}.skewBy(NAS2D::Vector{4, 6})));
}

TEST(Rectangle, skewInverseBy) {
	EXPECT_THROW((NAS2D::Rectangle{1, 1, 1, 1}.skewInverseBy(NAS2D::Vector{0, 0})), std::domain_error);
	EXPECT_THROW((NAS2D::Rectangle{1, 1, 1, 1}.skewInverseBy(NAS2D::Vector{0, 1})), std::domain_error);
	EXPECT_THROW((NAS2D::Rectangle{1, 1, 1, 1}.skewInverseBy(NAS2D::Vector{1, 0})), std::domain_error);

	EXPECT_EQ((NAS2D::Rectangle{2, 6, 4, 9}), (NAS2D::Rectangle{2, 6, 4, 9}.skewInverseBy(NAS2D::Vector{1, 1})));
	EXPECT_EQ((NAS2D::Rectangle{1, 2, 2, 3}), (NAS2D::Rectangle{2, 6, 4, 9}.skewInverseBy(NAS2D::Vector{2, 3})));
	EXPECT_EQ((NAS2D::Rectangle{0, 1, 1, 2}), (NAS2D::Rectangle{2, 6, 4, 9}.skewInverseBy(NAS2D::Vector{3, 4})));
}

TEST(Rectangle, operatorType) {
	EXPECT_EQ((NAS2D::Rectangle<int>{0, 0, 1, 1}), static_cast<NAS2D::Rectangle<int>>(NAS2D::Rectangle<float>{0.0, 0.0, 1.0, 1.0}));
	EXPECT_EQ((NAS2D::Rectangle<int>{1, 2, 3, 4}), static_cast<NAS2D::Rectangle<int>>(NAS2D::Rectangle<float>{1.0, 2.0, 3.0, 4.0}));

	EXPECT_EQ((NAS2D::Rectangle<float>{0.0, 0.0, 1.0, 1.0}), static_cast<NAS2D::Rectangle<float>>(NAS2D::Rectangle<int>{0, 0, 1, 1}));
	EXPECT_EQ((NAS2D::Rectangle<float>{1.0, 2.0, 3.0, 4.0}), static_cast<NAS2D::Rectangle<float>>(NAS2D::Rectangle<int>{1, 2, 3, 4}));
}

TEST(Rectangle, to) {
	EXPECT_EQ((NAS2D::Rectangle<int>{0, 0, 1, 1}), (NAS2D::Rectangle<float>{0.0, 0.0, 1.0, 1.0}.to<int>()));
	EXPECT_EQ((NAS2D::Rectangle<int>{1, 2, 3, 4}), (NAS2D::Rectangle<float>{1.0, 2.0, 3.0, 4.0}.to<int>()));

	EXPECT_EQ((NAS2D::Rectangle<float>{0.0, 0.0, 1.0, 1.0}), (NAS2D::Rectangle<int>{0, 0, 1, 1}.to<float>()));
	EXPECT_EQ((NAS2D::Rectangle<float>{1.0, 2.0, 3.0, 4.0}), (NAS2D::Rectangle<int>{1, 2, 3, 4}.to<float>()));
}

TEST(Rectangle, contains) {
	NAS2D::Rectangle rect = {1, 1, 2, 2};

	// Start point inclusive, and interior
	EXPECT_TRUE(rect.contains(NAS2D::Point{1, 1}));
	EXPECT_TRUE(rect.contains(NAS2D::Point{1, 2}));
	EXPECT_TRUE(rect.contains(NAS2D::Point{2, 1}));
	EXPECT_TRUE(rect.contains(NAS2D::Point{2, 2}));

	// Endpoint exclusive
	EXPECT_FALSE(rect.contains(NAS2D::Point{1, 3}));
	EXPECT_FALSE(rect.contains(NAS2D::Point{3, 1}));
	EXPECT_FALSE(rect.contains(NAS2D::Point{3, 3}));

	// Far out of bounds
	EXPECT_FALSE(rect.contains(NAS2D::Point{0, 0}));
	EXPECT_FALSE(rect.contains(NAS2D::Point{0, 4}));
	EXPECT_FALSE(rect.contains(NAS2D::Point{4, 0}));
	EXPECT_FALSE(rect.contains(NAS2D::Point{4, 4}));
}

TEST(Rectangle, overlaps) {
	NAS2D::Rectangle rect = {1, 1, 2, 2};

	// Identical overlap, and interior
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{1, 1, 2, 2}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{1, 1, 1, 1}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{1, 2, 1, 1}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{2, 1, 1, 1}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{2, 2, 1, 1}));

	// Partial overlap
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{0, 0, 2, 2}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{0, 2, 2, 2}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{2, 0, 2, 2}));
	EXPECT_TRUE(rect.overlaps(NAS2D::Rectangle{2, 2, 2, 2}));

	// Touching, with no overlap, 8 surrounding boxes
	// Corner points (bottom left, top left, bottom right, top right)
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{0, 0, 1, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{0, 3, 1, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{3, 0, 1, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{3, 3, 1, 1}));
	// Side edges (bottom, top, left, right)
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{1, 0, 2, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{1, 3, 2, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{0, 1, 1, 2}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{3, 1, 1, 2}));

	// Disjoint
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{-1, -1, 1, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{-1, 4, 1, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{4, -1, 1, 1}));
	EXPECT_FALSE(rect.overlaps(NAS2D::Rectangle{4, 4, 1, 1}));

	// No overlap for zero area, even if start point matches
	EXPECT_FALSE((NAS2D::Rectangle{0, 0, 0, 0}.overlaps(NAS2D::Rectangle{0, 0, 0, 0})));
}

TEST(Rectangle, Center) {
	EXPECT_EQ((NAS2D::Point{0, 0}), (NAS2D::Rectangle{-1, -1, 2, 2}.center()));
	EXPECT_EQ((NAS2D::Point{1, 1}), (NAS2D::Rectangle{0, 0, 2, 2}.center()));
	EXPECT_EQ((NAS2D::Point{2, 5}), (NAS2D::Rectangle{0, 0, 4, 10}.center()));
	EXPECT_EQ((NAS2D::Point{3, 8}), (NAS2D::Rectangle{1, 3, 4, 10}.center()));
}
