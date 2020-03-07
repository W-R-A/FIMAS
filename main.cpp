/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

/* FIMAS Project
 * Ross Andrewartha, January 2020
 */

#include "Networkbits.hpp"
#include "hardware.hpp"
#include "jsmn.h"

Thread t1;

static const char *JSON_STRING = "{\"devId\":\"1\",\"devName\":\"Sample Pump\",\"devType\":\"Peristaltic Pump\",\"devRelay\":\"Relay 1\",\"devTest\":\"Test Device\"},{\"devId\":\"2\",\"devName\":\"Switching Valve No.1\",\"devType\":\"Switching Valve\",\"devRelay\":\"Relay 2\",\"devTest\":\"Test Device\"}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int main() {
  int i;
  int r;
  jsmn_parser p;
  jsmntok_t t[128]; /* We expect no more than 128 tokens */

  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t,
                 sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    pc.printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT) {
    pc.printf("Object expected\n");
    return 1;
  }

  /* Loop over all keys of the root object */
  for (i = 1; i < r; i++) {
    if (jsoneq(JSON_STRING, &t[i], "devId") == 0) {
      /* We may use strndup() to fetch string value */
      pc.printf("- User: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "devName") == 0) {
      /* We may additionally check if the value is either "true" or "false" */
      pc.printf("- Admin: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "devType") == 0) {
      /* We may want to do strtol() here to get numeric value */
      pc.printf("- UID: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else {
      pc.printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
             JSON_STRING + t[i].start);
    }
  }
  return EXIT_SUCCESS;
}

// int main() {

// 	t1.start(networktest);
	
//     //Run POST, 5 times
//     post(5);

//     //Wait for button before starting routine
//     while(!userButton) {};
		
		
		

//     while (true) {
//         checkTiming();

//         //Speeded up by a factor of 10 for testing
//         //Delay used to set timing
//         thread_sleep_for(100);
//     }
// }
