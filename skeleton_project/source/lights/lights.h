/** @file
  * @brief Elevator panel light functionality
  *
  */

/** @brief Turns on lights by looping through the elevator orderlist
 *
 * @param elevator[in] elevator object which includes attribute orderlist
 */
void lights_update_from_orderlist(Elevator *elevator);

/** @brief Sets the elevator floor light to shine on the last visited valid floor. (not -1)
 *
 * @param elevator[in] elevator object pointer which includes the last reached floor
 */
void set_light_valid_floor_level (Elevator *elevator);