struct Soil
{
	float waterRetention; // can be too high or too low, resulting in waterlogging or lack of
			      // water
	float pH;	  // positively affects nutrients
	float nitrogen;	  // reduced leaf growth, if too much compared to phosphorus reduced root
			  // growth and susceptibility to disease
	float potassium;  //  water balance and resistance to disease
	float phosphorus; // root development and flower and fruiting
	float compaction; // usually negative or 0, negative means compacted. lowers waterRetention.
			  // raised with crop rotation or manual methods. lowered with more farming.
	float erosion;	  // usually negative or 0, negative means eroded, positive means extra
			  // artificial soil added. if reaches threshold soil tile may be destroyed
};
